#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H

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


enum Cities{
    sanfrancisco = "sanfrancisco",
    washington= "washington",
    newyork = "newyork",
    chicago = "chicago",
    minneapolis = "minneapolis",
    chattanooga = "chattanooga"
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
