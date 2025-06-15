#include "UserFunctions.h"
#include "IngredientFunctions.h"
#include "RecipeFunctions.h"
#include <fstream>
#include "json.hpp"
#include "Storage.h"
using namespace nlohmann;
using namespace crow;
using namespace std;

json::wvalue convertUserToJson(User user) 
{
    json::wvalue writeValueJson;
    writeValueJson["id"] = user.getId();
    writeValueJson["name"] = user.getName();
    writeValueJson["vegetarian"] = user.getVegetarian();
    
    crow::json::wvalue allergiesJson;
    int a = 0;
    for (const auto& ing : user.getAllergies()) {
        allergiesJson[a++] = convertIngredientToJson(ing);
    }

    // Ensure empty array instead of null
    if (a == 0) {
        allergiesJson = crow::json::wvalue::list();  // outputs as []
    }

    writeValueJson["allergies"] = std::move(allergiesJson);
    
    writeValueJson["bulk"] = user.getBulk();

    writeValueJson["mealPlan"] = crow::json::wvalue{};
    int r = 0;
    for (const auto& rec : user.getMealPlan()) {
        writeValueJson["mealPlan"][r++] = rec.getName();
    }
    return writeValueJson;
}

UserMap loadUsers(string filename){
    UserMap data;
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

        for (auto& item : jsonReadValue) 
        {
            int id = item["id"].i(); 
            string name = item["name"].s();
            bool vegetarian = item["vegetarian"].b();

            vector<Ingredient> algs;
            for (auto& a : item["allergies"]) {
                string aname = a["name"].s();
                int acal = a["calories"].i();
                bool aveg = (a["isVegan"].b() == true);
                algs.emplace_back(Ingredient(aname, acal, aveg));
            }

            bool bulk = item["bulk"].b();

            vector<Recipe> mplan;
            for (auto& r : item["mealPlan"]) 
            {
                string rec = r.s();
                mplan.push_back(recipesMap.at(rec));
            }
            
            User u{id, name, vegetarian, algs, bulk, mplan};
            data[u.getId()] = u;
        }
    }
        return data;
}

void saveUsers(UserMap data, const string filename){
     // Open the file for writing
     ofstream file(filename);

     if (file.is_open()) 
     {
        // Create a new JSON write value use to write to the file.
        json::wvalue jsonWriteValue;
         
        if (!data.empty()) 
        {
            int index = 0;
            for (const auto& [id, user] : data) 
            {
                jsonWriteValue[index++] = convertUserToJson(user);
            }
        } 
        else 
        {
            jsonWriteValue[0];
            jsonWriteValue = crow::json::wvalue{};
        }
        
        file << jsonWriteValue.dump();
        file.close();
     }
}

response createUser(const crow::request& req){
    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = json::load(req.body);

    // If there was a problem converting the body text to JSON return an error.
    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    // Create a new user.
    int id = readValueJson["id"].i();
    string name = readValueJson["name"].s();
    bool vegetarian = readValueJson["vegetarian"].b();

    vector<Ingredient> algs;
    for (auto& a : readValueJson["allergies"]) {
        string aname = a["name"].s();
        int acal = a["calories"].i();
        bool aveg = (a["isVegan"].b() == true);
        algs.push_back(Ingredient(aname, acal, aveg));
    }

    bool bulk = readValueJson["bulk"].b();

    vector<Recipe> mplan;
    for (auto& r : readValueJson["mealPlan"]) {
        string rec = r["name"].s();
        mplan.push_back(recipesMap.at(rec));
    }

    // Add the new user to the map.
    User user{id, name, vegetarian, algs, bulk, mplan};
    usersMap[user.getId()] = user;

    // Return the created user as a JSON string.
    return response(201, convertUserToJson(user).dump());
}

response readUser(int id){
    try 
    {
        // Get the user from the users map.
        User user = usersMap.at(id);

        // Return the user as a JSON string.
        return response(convertUserToJson(user).dump());
    } 
    catch (out_of_range& exception) 
    {
        // If the user was not found in the map return a 404 not found error.
        return response(404, "User Not Found");
    }
}

response readAllUsers(){
    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each user in the map, convert the user to JSON and add to the write value.
    int index = 0;
    for (auto& keyValuePair : usersMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = convertUserToJson(keyValuePair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

void updateUser(request req, response& res, int id) {
    try 
    {
        // Get the user from the users map.
        User user = usersMap.at(id);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON return an error.
        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the user.
        user.setName(readValueJson["name"].s());
        user.setVegetarian(readValueJson["vegetarian"].b());

        vector<Ingredient> newAllergies;
        int a = 0;
        for (auto& alr : readValueJson["allergies"]) {
            // Each allergy is a full Ingredient object in JSON
            string aname = alr["name"].s();
            int acal = alr["calories"].i();
            bool aveg = (alr["isVegan"].b() == true);
            newAllergies.push_back(Ingredient(aname, acal, aveg));
            ++a;
        }
        user.setAllergies(newAllergies);

        user.setBulk(readValueJson["bulk"].b());

        vector<Recipe> newPlan;
        int r = 0;
        for (auto& recs : readValueJson["mealPlan"]) {
            string rname = recs.s();
            Recipe rec = recipesMap.at(rname);
            newPlan.push_back(rec);
            ++r;
        }

        user.setMealPlan(newPlan);
        usersMap[id] = user;

        // Return the updated user as a JSON string.
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(convertUserToJson(user).dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        // If the user was not found in the map return a 404 not found error.
        res.code = 404;
        res.end("User Not Found");
    }
}

response deleteUser(int id) {
    try 
    {
        // Get the user from the users map.
        User user = usersMap.at(id);

        // Remove the user from the users map.
        usersMap.erase(id);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        // If the user was not found in the map return a 404 not found error.
        return response(404, "User not found");
    }
}
