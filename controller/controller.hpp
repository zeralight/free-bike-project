//
// Created by leo on 17/03/2017.
//

#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H

#include "controllerInterface.hpp"
#include "controllerDB.hpp"
#include "controllerUpdate.hpp"
class Controller
{
public:
    Controller();
    ~Controller();
    ControllerInterface * cI;
    ControllerDateBase * cDB;
    ControllerUpdate * cU;
  };

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
