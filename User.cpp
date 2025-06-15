#include "User.h"
#include "Storage.h"

// Default constructor
User::User()
    : id(0), name(""), vegetarian(false), bulk(false) {}

// Parameterized constructor
User::User(int userId,
           const std::string& userName,
           bool isVegetarian,
           const std::vector<Ingredient>& userAllergies,
           bool isBulk,
           const std::vector<Recipe>& userMealPlan)
    : id(userId),
      name(userName),
      vegetarian(isVegetarian),
      allergies(userAllergies),
      bulk(isBulk),
      mealPlan(userMealPlan){}

json User::toJson(){
    json aler = json::array();
    for (auto& ing : allergies)
        aler.push_back(ing.toJson());

    json recs = json::array();
    for (auto& rec : mealPlan)
        recs.push_back(rec.toJson());

    return json{
        {"id", id},
        {"name", name},
        {"vegetarian", vegetarian},
        {"allergies", aler},
        {"bulk", bulk},
        {"mealPlan", recs}
    };
}

User User::fromJson(const json& j){
    id = j.at("id").get<int>();
    name = j.at("name").get<std::string>();
    vegetarian = j.at("vegetarian").get<bool>();
    bulk = j.at("bulk").get<bool>();

    std::vector<Ingredient> alr;
    for (auto& a : j.at("allergies")) {
        Ingredient ing{
           a.at("name").get<std::string>(),
           a.at("calories").get<int>(),
           a.at("isVegan").get<bool>()
        };
        alr.push_back(ing);
    }

    std::vector<Recipe> meal;
    for (auto& r : j.at("mealPlan")) {
        Recipe rec = Recipe::fromJson(r);
        meal.push_back(rec);
    }

    return User(id, name, vegetarian, alr, bulk, meal);
}

// Setters
void User::setName(const std::string& newName) 
{
    name = newName;
}

void User::setVegetarian(bool isVegetarian) 
{
    vegetarian = isVegetarian;
}

void User::setAllergies(const std::vector<Ingredient>& newAllergies) 
{
    allergies = newAllergies;
}

void User::setBulk(bool isBulk) 
{
    bulk = isBulk;
}

void User::setMealPlan(const std::vector<Recipe>& plan)
{
    mealPlan = plan;
}

// Getters
int User::getId() const 
{
    return id;
}

std::string User::getName() const 
{
    return name;
}

bool User::getVegetarian() const 
{
    return vegetarian;
}

std::vector<Ingredient> User::getAllergies() const 
{
    return allergies;
}

bool User::getBulk() const 
{
    return bulk;
}

std::vector<Recipe> User::getMealPlan() const
{
    return mealPlan;
}