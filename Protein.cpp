#include "Protein.h"

// Default constructor
Protein::Protein()
    : Ingredient(), proteinGrams(0) {}

// Parameterized constructor
Protein::Protein(const std::string& name, int calories, bool isVegan, int pGrams)
    : Ingredient(name, calories, isVegan), proteinGrams(pGrams) {}

json Protein::toJson()
{
    return json{{"name", name}, {"calories", calories}, {"isVegan", isVegan}, {"proteinGrams", proteinGrams}};
}

// Getter
int Protein::getProtein() const 
{
    return proteinGrams;
}

// Setter
void Protein::setProtein(int pGrams) 
{
    proteinGrams = pGrams;
}