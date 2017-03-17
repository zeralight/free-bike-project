//
// Created by leo on 17/03/2017.
//

#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERDB_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERDB_H

#include "controller.hpp"
#include "../sgbd/Database.hpp"

class ControllerDB{
    ControllerDB();
    ~ControllerDB();
    DataBase * DB;

};
#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERDB_H
