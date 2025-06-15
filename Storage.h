#ifndef STORAGE_H
#define STORAGE_H

#pragma once
#include <vector>
#include <string>
#include "Storage.h"
#include "Ingredient.h" 
#include "Recipe.h" 
#include "User.h"
#include "json.hpp"
#include <fstream>

class Ingredient;
class Recipe;
class User;

//hardcoded presets
extern std::vector<Ingredient> presetIngredients;
extern std::vector<Recipe> presetRecipes;
extern std::vector<User> presetUsers;

using IngredientMap = std::map<std::string, Ingredient>;
using RecipeMap = std::map<std::string, Recipe>;
using UserMap = std::map<int, User>;

extern IngredientMap ingredientsMap;
extern RecipeMap recipesMap;
extern UserMap usersMap;

//void loadIngredients(const std::string& filename);
void saveIngredients(const std::string& filename);

//void loadRecipes(const std::string& filename);
void saveRecipes(const std::string& filename);

//void loadUsers(const std::string& filename);
void saveUsers(const std::string& filename);

#endif