#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLEROSM_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLEROSM_H

class ControllerOSM;

#include "controller.hpp"
/**
 * @brief This class is meant to deal with all the stuff related to the OSM data and views.
 * All the infos dealing with OSM are passing by this class.
 * @warning This class is not impleted yet so it not usable.
 */
class ControllerOSM{
public:
    ControllerOSM(Controller * controller);
    ~ControllerOSM();

private:
    Controller * controller;
};
#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLEROSM_H
