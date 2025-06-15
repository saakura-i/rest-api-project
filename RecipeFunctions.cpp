#include "RecipeFunctions.h"
#include "IngredientFunctions.h"
#include <fstream>
#include "json.hpp"
#include "Storage.h"
using namespace nlohmann;
using namespace crow;
using namespace std;

json::wvalue convertRecipeToJson(Recipe recipe) 
{
    json::wvalue writeValueJson;
    writeValueJson["name"] = recipe.getName();
    writeValueJson["nutrition"] = recipe.getNutrition();
    writeValueJson["bulk"] = recipe.getBulk();
    for (int i = 0; i < (int)recipe.getIngredients().size(); ++i) {
        writeValueJson["ingredients"][i] = convertIngredientToJson(recipe.getIngredients()[i]);
    }

    return writeValueJson;
}

RecipeMap loadRecipes(string filename){
    
    RecipeMap data;
    ifstream inFile(filename);
    if (inFile.is_open()) 
    {     
        // Create a stream for reading in the file.
        ostringstream stringStreamJson;
        
        // Read the entire JSON string.
        stringStreamJson << inFile.rdbuf();
        // Load the string into a JSON read value object.
        json::rvalue jsonReadValue = crow::json::load(stringStreamJson.str());
        // Close the file.
        inFile.close();

        // For each item in the JSON convert it to an object, 
        // and add it to the data map.
        for (json::rvalue r : jsonReadValue) 
        {
    
            string name = r["name"].s();
            string nutrition = r["nutrition"].s();
            bool bulk = r["bulk"].b();
            
            vector<Ingredient> comps;
            for (auto& i : r["ingredients"]) 
            {
                string iname = i["name"].s();
                int ical = i["calories"].i();
                bool iveg = i["isVegan"].b();
                comps.push_back(Ingredient(iname, ical, iveg));
            }

            Recipe rec{name, nutrition, bulk, comps};
            data[rec.getName()] = rec;   
        }
    }
    return data;
}

void saveRecipes(RecipeMap data, const string filename){
     // Open the file for writing
     ofstream file(filename);

     if (file.is_open()) 
     {
         // Create a new JSON write value use to write to the file.
         json::wvalue jsonWriteValue;
         
         // For each object in the map, convert the object to JSON and add to the write value.
         int index = 0;
         for (pair<string, Recipe> keyValuePair : data)
         {
             // first: gives you access to the first item in the pair.
             // second: gives you access to the second item in the pair.
             jsonWriteValue[index] = convertRecipeToJson(keyValuePair.second);
             index++;
         }
 
         // Write the JSON to the file.
         file << jsonWriteValue.dump();
         file.close();
     }
}

response createRecipe(request req){
    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = json::load(req.body);

    // If there was a problem converting the body text to JSON return an error.
    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    // Create a new recipe.
    vector<Ingredient> comps;
    for (auto& i : readValueJson["ingredients"]) {
        string iname = i["name"].s();
        int ical = i["calories"].i();
        bool iveg = (i["isVegan"].b() == true);
        comps.push_back(Ingredient(iname, ical, iveg));
    }

    Recipe recipe{readValueJson["name"].s(),
        readValueJson["nutrition"].s(),
        readValueJson["bulk"].b(),
        comps};

    // Add the new recipe to the map.
    recipesMap[recipe.getName()] = recipe;

    // Return the created recipe as a JSON string.
    return response(201, convertRecipeToJson(recipe).dump());
}

response readRecipe(string name){
    try 
    {
        // Get the recipe from the recipes map.
        Recipe recipe = recipesMap.at(name);

        // Return the recipe as a JSON string.
        return response(convertRecipeToJson(recipe).dump());
    } 
    catch (out_of_range& exception) 
    {
        // If the recipe was not found in the map return a 404 not found error.
        return response(404, "Recipe Not Found");
    }
}

response readAllRecipes(){
    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each recipe in the map, convert the recipe to JSON and add to the write value.
    int index = 0;
    for (pair<string, Recipe> keyValuePair : recipesMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = convertRecipeToJson(keyValuePair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

void updateRecipe(request req, response& res, string name){
    try 
    {
        // Get the recipe from the recipes map.
        Recipe recipe = recipesMap.at(name);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON return an error.
        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the recipe.
        vector<Ingredient> comps;
        for (auto& i : readValueJson["ingredients"]) {
            string iname = i["name"].s();
            int ical = i["calories"].i();
            bool iveg = (i["isVegan"].b() == true);
            comps.push_back(Ingredient(iname, ical, iveg));
        }

        recipe.setNutrition(readValueJson["nutrition"].s());
        recipe.setBulk(readValueJson["bulk"].b());
        recipe.setIngredients(comps);

        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(convertRecipeToJson(recipe).dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        // If the recipe was not found in the map return a 404 not found error.
        res.code = 404;
        res.end("Recipe Not Found");
    }
}

response deleteRecipe(string name){
    try 
    {
        // Get the recipe from the recipes map.
        Recipe recipe = recipesMap.at(name);

        // Remove the recipe from the recipes map.
        recipesMap.erase(name);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        // If the recipe was not found in the map return a 404 not found error.
        return response(404, "Recipe not found");
    }
}
