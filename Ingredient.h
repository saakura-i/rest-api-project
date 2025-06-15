#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include "json.hpp"
using namespace nlohmann;

class Ingredient 
{
    protected:
        std::string name;
        int calories;
        bool isVegan;
    public:
        // Constructors
        Ingredient();
        Ingredient(const std::string& name, int calories, bool isVegan);
        json toJson() const;
        static Ingredient fromJson(const json &j);

        //Getters -> do we need getIngredient?
        std::string getName() const;
        int getCalories() const;
        bool getVegan() const;

        //Setters
        void setName(const std::string& name);
        void setCalories(int calories);
        void setVegan(bool isVegan);
        
};

#endif