#include "Ingredient.h"

// Default constructor
Ingredient::Ingredient()
    : name(""), calories(0), isVegan(false) {}

// Parameterized constructor
Ingredient::Ingredient(const std::string& name, int calories, bool isVegan)
    : name(name), calories(calories), isVegan(isVegan) {}

json Ingredient::toJson() const{
    return json{{"name", name}, {"calories", calories}, {"isVegan", isVegan}};
}

Ingredient Ingredient::fromJson(const json &j) {
    return Ingredient(
        j.at("name").get<std::string>(),
        j.at("calories").get<int>(),
        j.at("isVegan").get<bool>()
    );
}

// Getters
std::string Ingredient::getName() const 
{
    return name;
}

int Ingredient::getCalories() const 
{
    return calories;
}

bool Ingredient::getVegan() const 
{
    return isVegan;
}

// Setters
void Ingredient::setName(const std::string& newName) 
{
    name = newName;
}

void Ingredient::setCalories(int newCalories) 
{
    calories = newCalories;
}

void Ingredient::setVegan(bool vegan) 
{
    isVegan = vegan;
}