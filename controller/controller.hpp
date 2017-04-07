#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H

class Controller;

enum Cities{
    SANFRANCISCO=1,
    WASHINGTON=2,
    NEWYORK=3,
    CHICAGO=4,
    MINNEAPOLIS=5,
    CHATTANOOGA=6
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
    void runInterface();
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
