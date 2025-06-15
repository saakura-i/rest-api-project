#include "IngredientFunctions.h"
#include "Storage.h"
#include <fstream>
#include "json.hpp"
using namespace nlohmann;
using namespace crow;
using namespace std;

vector<string> proteinIds;
vector<string> carbIds;
vector<string> fatIds;

json::wvalue convertIngredientToJson(const Ingredient& ingredient) 
{
    json::wvalue writeValueJson;
    writeValueJson["name"] = ingredient.getName();
    writeValueJson["calories"] = ingredient.getCalories();
    writeValueJson["isVegan"] = ingredient.getVegan();
    return writeValueJson;
}

IngredientMap loadIngredients(string filename)
{
    IngredientMap data;
    ifstream inFile(filename);
    if (inFile.is_open()) 
    {      
        // Create a stream for reading in the file.
        ostringstream stringStreamJson;

        // Read the entire JSON string.
        stringStreamJson << inFile.rdbuf();

        // Load the string into a JSON read value object.
        json::rvalue jsonReadValue = json::load(stringStreamJson.str());

        // Close the file.
        inFile.close();

        // For each item in the JSON convert it to an object, 
        // and add it to the data map.
        for (json::rvalue ingredient : jsonReadValue) 
        {
            string name = ingredient["name"].s();
            int calories = ingredient["calories"].i();
            bool isVegan = ingredient["isVegan"].b();

            Ingredient ing{name, calories, isVegan};
            data[ing.getName()] = ing;  

            if (ingredient.has("proteinGrams")) {
                proteinIds.push_back(name);
            } else if (ingredient.has("carbGrams")) {
                carbIds.push_back(name);
            } else if (ingredient.has("fatGrams")) {
                fatIds.push_back(name);
            }
        }
    }
    return ingredientsMap = data;
}

void saveIngredients(IngredientMap data, const string filename){
     // Open the file for writing
     ofstream file(filename);

     if (file.is_open()) 
     {
         // Create a new JSON write value use to write to the file.
         crow::json::wvalue jsonWriteValue;
         
         // For each object in the map, convert the object to JSON and add to the write value.
         int index = 0;
         for (pair<string, Ingredient> keyValuePair : data)
         {
             // first: gives you access to the first item in the pair.
             // second: gives you access to the second item in the pair.
             jsonWriteValue[index] = convertIngredientToJson(keyValuePair.second);
             index++;
         }
 
         // Write the JSON to the file.
         file << jsonWriteValue.dump();
         file.close();
     }
}

response createIngredient(request req){
    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = crow::json::load(req.body);

    // If there was a problem converting the body text to JSON return an error.
    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    // Create a new ingredient.
    string name = readValueJson["name"].s();
    int calories = readValueJson["calories"].i();
    bool isVegan  = (readValueJson["isVegan"].b() == true);

    Ingredient ing{name, calories, isVegan};
    ingredientsMap[ing.getName()] = ing;
    return response(201, convertIngredientToJson(ing).dump());
}

response readIngredient(string name){
    try 
    {
        // Get the ingredient from the ingredients map.
        Ingredient ingredient = ingredientsMap.at(name);

        // Return the ingredient as a JSON string.
        return response(convertIngredientToJson(ingredient).dump());
    } 
    catch (out_of_range& exception) 
    {
        // If the ingredient was not found in the map return a 404 not found error.
        return response(404, "Ingredient Not Found");
    }
}

response readProteinIngredients() {
    json::wvalue arr;
    int i=0;
    for (auto& id : proteinIds)
        arr[i++] = convertIngredientToJson(ingredientsMap[id]);
    return response(arr.dump());
}

response readCarbIngredients() {
    json::wvalue arr;
    int i=0;
    for (auto& id : carbIds)
        arr[i++] = convertIngredientToJson(ingredientsMap[id]);
    return response(arr.dump());
}

response readFatIngredients() {
    json::wvalue arr;
    int i=0;
    for (auto& id : fatIds)
        arr[i++] = convertIngredientToJson(ingredientsMap[id]);
    return response(arr.dump());
}

response readAllIngredients(){
    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each ingredient in the map, convert the ingredient to JSON and add to the write value.
    int index = 0;
    for (pair<string, Ingredient> keyValuePair : ingredientsMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = convertIngredientToJson(keyValuePair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

void updateIngredient(request req, response& res, string name){
    try 
    {
        // Get the ingredient from the ingredients map.
        Ingredient ingredient = ingredientsMap.at(name);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON return an error.
        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the ingredient.
        ingredient.setCalories(readValueJson["calories"].i());
        ingredient.setVegan(readValueJson["isVegan"].b());
        ingredientsMap[name] = ingredient;

        // Return the updated ingredient as a JSON string.
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(convertIngredientToJson(ingredient).dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        // If the ingredient was not found in the map return a 404 not found error.
        res.code = 404;
        res.end("Ingredient Not Found");
    }
}

response deleteIngredient(string name){
    try 
    {
        // Get the ingredient from the ingredients map.
        Ingredient ingredient = ingredientsMap.at(name);

        // Remove the ingredient from the ingredients map.
        ingredientsMap.erase(name);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        // If the ingredient was not found in the map return a 404 not found error.
        return response(404, "Ingredient not found");
    }
}
