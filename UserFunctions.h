#ifndef USER_FUNCTIONS_H
#define USER_FUNCTIONS_H

#pragma once
#include <crow.h>
#include <map>
#include <string>
#include "User.h"
#include "Storage.h"

UserMap loadUsers(std::string filename);
void saveUsers(UserMap data, const std::string filename);

crow::json::wvalue convertUserToJson(User user); 
crow::response createUser(const crow::request& req);
crow::response readUser(int id);
crow::response readAllUsers();
void updateUser(crow::request req, crow::response& res, int id);
crow::response deleteUser(int id);

#endif