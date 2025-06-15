#include "Carbs.h"

// Default constructor
Carbs::Carbs()
    : Ingredient(), carbGrams(0) {}

// Parameterized constructor
Carbs::Carbs(const std::string& name, int calories, bool isVegan, int cGrams)
    : Ingredient(name, calories, isVegan), carbGrams(cGrams) {}

json Carbs::toJson()
{
    return json{{"name", name}, {"calories", calories}, {"isVegan", isVegan}, {"carbGrams", carbGrams}};
}

// Getter
int Carbs::getCarbs() const 
{
    return carbGrams;
}

// Setter
void Carbs::setCarbs(int cGrams) 
{
    carbGrams = cGrams;
}