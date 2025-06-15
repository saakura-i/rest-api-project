#ifndef PROTEIN_H
#define PROTEIN_H

#include <string>
#include <vector>
#include "Ingredient.h"

class Protein : public Ingredient 
{
    private:
        int proteinGrams;
    
    public:
        // Constructors
        Protein();
        Protein(const std::string& name, int calories, bool isVegan, int pGrams);
        json toJson();
    
        //Getters
        int getProtein() const;

        //Setters
        void setProtein(int pGrams);
};

#endif