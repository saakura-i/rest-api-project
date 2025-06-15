#ifndef INGREDIENT_FUNCTIONS_H
#define INGREDIENT_FUNCTIONS_H

#include <crow.h>
#include <map>
#include <string>
#include "Ingredient.h"
#include "Storage.h"

extern std::vector<std::string> proteinIds;
extern std::vector<std::string> carbIds;
extern std::vector<std::string> fatIds;

IngredientMap loadIngredients(std::string filename);
void saveIngredients(IngredientMap data, const std::string filename);

crow::json::wvalue convertIngredientToJson(const Ingredient& ingredient);
crow::response createIngredient(crow::request req);
crow::response readIngredient(std::string name);
crow::response readProteinIngredients();
crow::response readCarbIngredients();
crow::response readFatIngredients();
crow::response readAllIngredients();
void updateIngredient(crow::request req, crow::response& res, const std::string name);
crow::response deleteIngredient(std::string name);

#endif
