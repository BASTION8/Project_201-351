#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QString>

QString authorize(std::string login, std::string password);
int* start(int * field);
int* set_coord(std::string message, int pos, int* field);
//QString stats();
//int* action(int* field);

#endif // FUNCTIONS_H
