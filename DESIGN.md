# Project Design Document

## Introduction
Meal planner for different types of people like office workers, gym goers, people on diets etc.
The meal plan they would get would differ based on dietary preferences, available ingredients, and nutritional goals.
The API would give personalized meal suggestions, allow saving of weekly meal plans, and manage pantry inventory.

## Background/Context
Meal planner designed to help users simplify their daily food planning. Users can browse or search for recipes based on their goals, build meal plans using these recipes with a vector, and track ingredients they have on hand.

## Stakeholders
- Users: Home cooks, busy professionals, fitness enthusiasts.
- Developers: Developers can build mobile/web apps on top of this API.
- Nutritionists: Could integrate this into patient meal plan tools.

## Functional Requirements
- Users can create accounts and set preferences.
- Recipes can be added, viewed, or searched.
- Users can build meal plans for the week.


## Use Case Description
- As a user, I want to search for ingredients based on food type
- As a user, I want to create a mealplan composed of recipes
- As a user, I want to browse all recipes
- As a user, I want to look into a specific recipe
- As a user, I want to delete a user's profile
- As a user, I want to update a user's profile
- As a user, I want to read a user's profile info
- As a user, I want to read all user profiles
- As a user, I want to create a new user profile
- As an admin, I want to create a new recipe
- As an admin, I want to update a recipe
- As an admin, I want to delete a recipe
- As an admin, I want to create a new ingredient
- As an admin, I want to delete an ingredient

## List Of Resources
Look at UML diagram

## List of End Points
User Endpoints
    GET /users
    GET /users/{id}
    POST /users
    PUT /users/{id}:
    DELETE /users/{id}
Ingredient Endpoints
    GET /ingredients - all ingredients
    GET /ingredients/{name} - all ingredients
    GET /ingredients/protein - protein-only
    GET /ingredients/carb - carbs-only
    GET /ingredients/fat - fat-only
    GET /ingredients/{name} - single ingredient    
For admin only:
        POST /ingredients - add new ingredient
        DELETE /ingredients/{name}:
Recipe Endpoints
    GET /recipes
    GET /recipes/{name}
For admin only:
        POST /recipes
        UPDATE /recipes/{name}
        DELETE /recipes/{name}


## UML Diagrams
https://docs.google.com/drawings/d/1S5i-0gTAY2_-YfK9shCLD6MMSEgdLTMC1ebA_cEaDog/edit?usp=sharing

