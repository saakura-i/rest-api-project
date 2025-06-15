#ifndef CARBS_H
#define CARBS_H

#include <string>
#include <vector>
#include "Ingredient.h"

class Carbs : public Ingredient 
{
    private:
        int carbGrams;
    
    public:
        // Constructors
        Carbs();
        Carbs(const std::string& name, int calories, bool isVegan, int cGrams);
        json toJson();
    
        //Getters
        int getCarbs() const;

        //Setters
        void setCarbs(int cGrams);
};

#endif