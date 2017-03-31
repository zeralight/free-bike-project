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
  };

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
