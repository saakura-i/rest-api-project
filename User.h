#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Ingredient.h"
#include "Recipe.h"
#include "json.hpp"
using namespace nlohmann;

class User 
{
    protected:
        int id;
        std::string name;
        bool vegetarian;
        std::vector<Ingredient> allergies;
        bool bulk;
        std::vector<Recipe> mealPlan;
    
    public:
        // Constructors
        User();
        User(int userId,
             const std::string& userName,
             bool isVegetarian,
             const std::vector<Ingredient>& userAllergies,
             bool isBulk,
             const std::vector<Recipe>& userMealPlan);
        
        json toJson();
        User fromJson(const json& j);
    
        // Setters
        void setName(const std::string& newName);
        void setVegetarian(bool isVegetarian);
        void setAllergies(const std::vector<Ingredient>& newAllergies);
        void setBulk(bool isBulk);
        void setMealPlan(const std::vector<Recipe>& plan);
    
        // Getters
        int getId() const;
        std::string getName() const;
        bool getVegetarian() const;
        std::vector<Ingredient> getAllergies() const;
        bool getBulk() const;
        std::vector<Recipe> getMealPlan() const;
};

#endif
