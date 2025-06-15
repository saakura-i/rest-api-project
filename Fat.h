#ifndef FAT_H
#define FAT_H

#include <string>
#include <vector>
#include "Ingredient.h"

class Fat : public Ingredient 
{
    private:
        int fatGrams;
    
    public:
        // Constructors
        Fat();
        Fat(const std::string& name, int calories, bool isVegan, int fGrams);
        json toJson();
    
        //Getters
        int getFat() const;

        //Setters
        void setFat(int fGrams);
};

#endif