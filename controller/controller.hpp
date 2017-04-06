#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H

class Controller;

enum Cities{
    SANFRANCISCO,
    WASHINGTON,
    NEWYORK,
    CHICAGO,
    MINNEAPOLIS,
    CHATTANOOGA
};


#include "controllerInterface.hpp"
#include "controllerUpdate.hpp"
#include "controllerOSM.hpp"

class Controller
{
public:
    Controller();
    ~Controller();
    ControllerInterface * cI;
    ControllerUpdate * cU;
    ControllerOSM * cOSM;
    void activateCity(enum Cities city);
  };

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
