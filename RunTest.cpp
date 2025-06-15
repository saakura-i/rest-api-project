#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "IngredientFunctions.h"
#include "RecipeFunctions.h"
#include "UserFunctions.h"

static void reset()
{
    ingredientsMap = loadIngredients("ingredients.json");
    std::cout << "1" << std::endl;
    recipesMap     = loadRecipes("recipes.json");
    std::cout << "2" << std::endl;
    usersMap       = loadUsers("users.json");
    std::cout << "3" << std::endl;
}

TEST_CASE("IngredientFunctions load & CRUD") 
{
    reset();
    
    SUBCASE("loadIngredients() should read 4 items") 
    {
        CHECK(ingredientsMap.size() == 20);
    }

    SUBCASE("readAllIngredients() returns correct JSON array") 
    {
        auto resp = readAllIngredients();
        auto jsonArr = crow::json::load(resp.body);
        CHECK(jsonArr.size() == 20);
    }

    SUBCASE("createIngredient() then readIngredient()") 
    {
        crow::request req;
        req.body = R"(
          {"name":"almond","calories": 575,"isVegan": true}
        )";
        auto c = createIngredient(req);
        CHECK(c.code == 201);

        // Now read it back
        auto r = readIngredient("almond");
        auto j = crow::json::load(r.body);
        CHECK(j["name"].s() == "almond");
        CHECK(j["calories"].i() == 575);
        CHECK(j["isVegan"].b() == true);
    }

    SUBCASE("Filtering endpoints (protein/carb/fat)") 
    {
        auto p = readProteinIngredients();
        CHECK(crow::json::load(p.body).size() > 0);

        auto c = readCarbIngredients();
        CHECK(crow::json::load(c.body).size() > 0);

        auto f = readFatIngredients();
        CHECK(crow::json::load(f.body).size() > 0);
    }
}

TEST_CASE("RecipeFunctions load & CRUD") 
{
    reset();

    SUBCASE("loadRecipes reads 10 recipes") 
    {
        CHECK(recipesMap.size() == 10);
    }

    SUBCASE("readAllRecipes returns correct array") 
    {
        auto r = readAllRecipes();
        auto arr = crow::json::load(r.body);
        CHECK(arr.size() == 10);
    }

    SUBCASE("createRecipe then readRecipe") 
    {
        crow::request req;
        req.body = R"(
          {
            "name":"rice_egg",
            "nutrition":"250 kcal",
            "bulk": true,
            "ingredients":[
              {"name":"rice","calories":130,"isVegan":true},
              {"name":"egg","calories":155,"isVegan":false}
            ]
          }
        )";
        auto c = createRecipe(req);
        CHECK(c.code == 201);

        auto rr = readRecipe("rice_egg");
        auto jr = crow::json::load(rr.body);
        CHECK(jr["name"].s() == "rice_egg");
        CHECK(jr["ingredients"].size() == 2);
    }
}

TEST_CASE("UserFunctions load & CRUD") 
{
    reset();
    
    SUBCASE("loadUsers reads 5 users") 
    {
        CHECK(usersMap.size() == 5);
    }

    SUBCASE("readAllUsers returns correct array") 
    {
        auto r = readAllUsers();
        auto arr = crow::json::load(r.body);
        CHECK(arr.size() == 5);
    }

    SUBCASE("readUser(1) == Michael with omelette") 
    {
        auto r = readUser(1);
        auto j = crow::json::load(r.body);
        CHECK(j["name"].s() == "Michael");
        CHECK(j["mealPlan"].size() == 2);
        CHECK(j["mealPlan"][1]["name"].s() == "cheese_omelette");
    }

    SUBCASE("updateUser changes bulk flag") 
    {
        crow::request req;
        req.body = R"(
          {
            "id": 1,
            "name": "Michael",
            "vegetarian": false,
            "bulk": true,
            "allergies": [
                { "name": "olive oil", "calories": 884, "isVegan": true}
            ],
            "mealPlan": ["omelette", "cheese_omelette"]
          }
        )";
        crow::response res;
        updateUser(req, res, 1);
        CHECK(res.code == 200);

        auto r2 = readUser(1);
        auto j2 = crow::json::load(r2.body);
        CHECK(j2["bulk"].b() == true);
    }
}
