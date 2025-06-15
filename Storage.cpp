#include "Storage.h"
#include <fstream>
#include "json.hpp"
using namespace nlohmann;

std::vector<Ingredient> presetIngredients;
std::vector<Recipe> presetRecipes;
std::vector<User> presetUsers;

IngredientMap ingredientsMap;
RecipeMap recipesMap;
UserMap usersMap;

// void loadIngredients(const std::string& filename) 
// {
//     std::ifstream inFile(filename);
//     if (!inFile.is_open()) return;

//     json j;
//     inFile >> j;

//     for (auto& i : j) {
//         Ingredient ing = Ingredient::fromJson(i);
//         ingredientsMap[ing.getName()] = ing;
//         presetIngredients.push_back(ing);
//     }
// }

void saveIngredients(const std::string& filename) 
{
    json j = json::array();
    for (auto& i : ingredientsMap) {
        j.push_back(i.second.toJson());
    }
    std::ofstream outFile(filename);
    outFile << j.dump(4);
}

void loadRecipes(const std::string& filename) 
{
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return;

    json j;
    inFile >> j;

    for (auto& r : j) {
        Recipe rec = Recipe::fromJson(r);
        recipesMap[rec.getName()] = rec;
        presetRecipes.push_back(rec);
    }
}

void saveRecipes(const std::string& filename) 
{
    json j = json::array();
    for (auto& r : recipesMap) {
        j.push_back(r.second.toJson());
    }
    std::ofstream outFile(filename);
    outFile << j.dump(4);
}

void loadUsers(const std::string& filename) 
{
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return;

    json j;
    inFile >> j;

    for (auto& u : j) {
        int id = u.at("id").get<int>();
        std::string name = u.at("name").get<std::string>();
        bool vegetarian = u.at("vegetarian").get<bool>();
        bool bulk = u.at("bulk").get<bool>();

        std::vector<Ingredient> allergies;
        for (auto& a : u.at("allergies")) {
            Ingredient ing = Ingredient::fromJson(a);
            allergies.push_back(ing);
        }

        std::vector<Recipe> mealPlan;
        for (auto& rname : u.at("mealPlan")) {
            std::string recipeName = rname.get<std::string>();
            if (recipesMap.count(recipeName)) {
                mealPlan.push_back(recipesMap[recipeName]);
            }
        }

        User user(id, name, vegetarian, allergies, bulk, mealPlan);
        usersMap[user.getId()] = user;
        presetUsers.push_back(user);
    }
}

void saveUsers(const std::string& filename) 
{
    json j = json::array();
    for (auto& u : usersMap) {
        j.push_back(u.second.toJson());
    }
    std::ofstream outFile(filename);
    outFile << j.dump(4);
}