#include "Fat.h"

// Default constructor
Fat::Fat()
    : Ingredient(), fatGrams(0) {}

// Parameterized constructor
Fat::Fat(const std::string& name, int calories, bool isVegan, int fGrams)
    : Ingredient(name, calories, isVegan), fatGrams(fGrams) {}

json Fat::toJson()
{
    return json{{"name", name}, {"calories", calories}, {"isVegan", isVegan}, {"fatGrams", fatGrams}};
}

// Getter for fatGrams
int Fat::getFat() const 
{
    return fatGrams;
}

// Setter for fatGrams
void Fat::setFat(int fGrams) 
{
    fatGrams = fGrams;
}