#include "functions.h"

QString authorize(std::string login, std::string password)
{
    QString result;
    if (login =="admin" && password == "123")
        result = "admin";
    else if (login =="manager" && password == "123")
        result = "manager";
    else if (login == "user" && password == "123")
        result = "user";
    else
        result = "authorization error";
    return result;
}

int* start(int * field)
{
    for(int i=0; i<200; i++) {
        field[i] = 0;
    }
    return field;
}

int* set_coord(std::string message, int pos, int* field)
{
    std::string player1_ships = "";
    std::string player2_ships = "";

    pos = message.find("&");
    player1_ships = message.substr(0, pos);
    message.erase(0, pos);
    for(int i=0; i<100; i++) {
        field[i] = player1_ships[i];
    }

    pos = message.find("&");
    player2_ships = message.substr(pos+1, message.length() - 3);
    message.erase(0);
    for(int i=0; i<100; i++) {
        field[i] = player2_ships[i];
    }
    return field;
}

//int* action(int* field)
//{
//
//}
