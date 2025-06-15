#include <crow.h>
#include "IngredientFunctions.h"
#include "RecipeFunctions.h"
#include "UserFunctions.h"
#include "Storage.h"


static const std::string ADMIN_CODE = "password";

int main(){
    ingredientsMap = loadIngredients("ingredients.json");
    recipesMap = loadRecipes("recipes.json");
    usersMap = loadUsers("users.json");

    crow::SimpleApp app;

    auto isAdmin = [&](const crow::request& req){
        auto code = req.url_params.get("admin_code");
        return (code && ADMIN_CODE == code);
    };

    // Ingredient routes
    CROW_ROUTE(app,"/api/ingredients").methods("GET"_method) (readAllIngredients);
    CROW_ROUTE(app,"/api/ingredients/<string>").methods("GET"_method)(readIngredient);
    CROW_ROUTE(app, "/api/ingredients/protein").methods("GET"_method)(readProteinIngredients);
    CROW_ROUTE(app, "/api/ingredients/carb").methods("GET"_method)(readCarbIngredients);
    CROW_ROUTE(app, "/api/ingredients/fat").methods("GET"_method)(readFatIngredients);
    CROW_ROUTE(app,"/api/ingredients/<string>").methods("PUT"_method)(updateIngredient);

    // Admin only:
    CROW_ROUTE(app, "/api/ingredients").methods("POST"_method)([&](const crow::request& req) -> crow::response{
        if (!isAdmin(req)) {
            return crow::response(403, "Admin code required");
        }
        return createIngredient(req);
    });

    CROW_ROUTE(app, "/api/ingredients/<string>").methods("DELETE"_method)([&](const crow::request& req, crow::response& res, const std::string& name) {
        if (!isAdmin(req)) {
            res.code = 403;
            res.end("Admin code required");
            return;
        }
        deleteIngredient(name);
        res.code = 204;
        res.end();
    });

    // Recipe routes
    CROW_ROUTE(app,"/api/recipes").methods("GET"_method) (readAllRecipes);
    CROW_ROUTE(app,"/api/recipes/<string>").methods("GET"_method)(readRecipe);

    // Admin-only:
    CROW_ROUTE(app, "/api/recipes").methods("POST"_method)([&](const crow::request& req) -> crow::response {
        if (!isAdmin(req)) {
            return crow::response(403, "Admin code required");
        }
        return createRecipe(req);
    });

    CROW_ROUTE(app, "/api/recipes/<string>").methods("DELETE"_method)([&](const crow::request& req, crow::response& res, const std::string& name) {
        if (!isAdmin(req)) {
            res.code = 403;
            res.end("Admin code required");
            return;
        }
        deleteRecipe(name);
        res.code = 204;
        res.end();
    });

    CROW_ROUTE(app,"/api/recipes/<string>").methods("PUT"_method)([&](const crow::request& req, crow::response& res, const std::string& name) {
        if (!isAdmin(req)) {
            res.code = 403;
            res.end("Admin code required");
            return;
        }
        updateRecipe(req, res, name);
    });

    // User routes
    CROW_ROUTE(app,"/api/users").methods("POST"_method)(createUser);
    CROW_ROUTE(app,"/api/users").methods("GET"_method) (readAllUsers);
    CROW_ROUTE(app,"/api/users/<int>").methods("GET"_method)(readUser);
    CROW_ROUTE(app,"/api/users/<int>").methods("PUT"_method)(updateUser);
    CROW_ROUTE(app,"/api/users/<int>").methods("DELETE"_method)(deleteUser);

    // Start server
    app.port(17381).run();

    // Save on exit
    saveIngredients(ingredientsMap, "ingredients.json");
    saveRecipes(recipesMap, "recipes.json");
    saveUsers(usersMap, "users.json");

    return 0;
}
