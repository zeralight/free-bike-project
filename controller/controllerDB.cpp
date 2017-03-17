//
// Created by leo on 17/03/2017.
//

#include "controllerDB.hpp"

ControllerDB::ControllerDB() {
    initDB();
    DB = newDB("Dat Base");
}

ControllerDB::~ControllerDB() {
    delDB(DB);
}