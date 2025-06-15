#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>
#include "Ingredient.h"
#include "json.hpp"
using namespace nlohmann;

class Recipe 
{
    protected:
        std::string name;
        std::string nutrition;
        bool bulk;
        std::vector<Ingredient> ingredients;
    
    public:
        //constructors
        Recipe();
        Recipe(const std::string& name, 
               const std::string& nutrition, 
               bool bulk, 
               const std::vector<Ingredient>& ingredients);

        json toJson() const;
        static Recipe fromJson(const json &j);
        
        //setters
        void setName(const std::string& name);
        void setNutrition(const std::string& nutrition);
        void setBulk(bool bulk);
        void setIngredients(const std::vector<Ingredient>& ingredients);
       
        //getters -> do we need getRecipe?
        std::string getName() const;
        std::string getNutrition() const;
        bool getBulk() const;
        std::vector<Ingredient> getIngredients() const;
        
        //function to calculate calories
        int calcCal() const;
};

#endif