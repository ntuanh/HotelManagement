#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "../Objects/history.h"
#include "../Objects/hotels.h"
#include "../Objects/users.h"

int userInterface(historyManager manager, ListHotel hotels, ListUser users);
DataUser signInUser();
DataUser signUpUser( historyManager manager);
void saveHistory(historyManager list, int id, DataHistory data);

#endif 