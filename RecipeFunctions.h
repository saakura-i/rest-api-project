#ifndef RECIPE_FUNCTIONS_H
#define RECIPE_FUNCTIONS_H

#include <crow.h>
#include <map>
#include <string>
#include "Recipe.h"
#include "Storage.h"

RecipeMap loadRecipes(std::string filename);
void saveRecipes(RecipeMap data, const std::string filename);

crow::json::wvalue convertRecipeToJson(Recipe recipe);
crow::response createRecipe(crow::request req);
crow::response readRecipe(std::string name);
crow::response readAllRecipes();
void updateRecipe(crow::request req, crow::response& res, const std::string name);
crow::response deleteRecipe(std::string name);

#endif
