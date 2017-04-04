#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLEROSM_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLEROSM_H
#include "controller.hpp"
class ControllerOSM{
public:
    ControllerOSM(Controller * controller);
    ~ControllerOSM();

private:
    Controller * controller;
};
#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLEROSM_H
