#include "Recipe.h"

// Default constructor
Recipe::Recipe()
    : name(""), nutrition(""), bulk(false) {}

// Parameterized constructor
Recipe::Recipe(const std::string& name,
               const std::string& nutrition,
               bool bulk,
               const std::vector<Ingredient>& ingredients)
    : name(name), nutrition(nutrition), bulk(bulk), ingredients(ingredients) {}

json Recipe::toJson() const{
    json arr = json::array();
    for (auto &ingredient : ingredients)
        arr.push_back(ingredient.toJson());
    return json{
        {"name", name},
        {"nutrition", nutrition},
        {"bulk", bulk},
        {"ingredients", arr}
    };
}

Recipe Recipe::fromJson(const json &j){
    std::string name = j.at("name").get<std::string>();
    std::string nutrition = j.at("nutrition").get<std::string>();
    bool bulk = j.at("bulk").get<bool>();

    std::vector<Ingredient> ings;
    for (auto& i : j.at("ingredients")) {
        Ingredient ing = Ingredient::fromJson(i);
        ings.push_back(ing);
    }

    return Recipe(name, nutrition, bulk, ings);
}

// Setters
void Recipe::setName(const std::string& newName) 
{
    name = newName;
}

void Recipe::setNutrition(const std::string& newNutrition) 
{
    nutrition = newNutrition;
}

void Recipe::setBulk(bool isBulk) 
{
    bulk = isBulk;
}

void Recipe::setIngredients(const std::vector<Ingredient>& newIngredients) 
{
    ingredients = newIngredients;
}

// Getters
std::string Recipe::getName() const 
{
    return name;
}

std::string Recipe::getNutrition() const 
{
    return nutrition;
}

bool Recipe::getBulk() const 
{
    return bulk;
}

std::vector<Ingredient> Recipe::getIngredients() const 
{
    return ingredients;
}

// Function to calculate total calories from all ingredients
int Recipe::calcCal() const 
{
    int totalCalories = 0;
    for (auto& ingredient : ingredients) 
    {
        totalCalories += ingredient.getCalories();
    }
    return totalCalories;
}
