//
// Created by leo on 17/03/2017.
//

#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERUPDATE_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERUPDATE_H

#ifndef SCRIPT_FILES_DL
    #define SCRIPT_FILES_DL "../download_bike/"
#endif
#include <wrappy/wrappy.h>
#include "controller.hpp"
class ControllerUpdate{
    ControllerUpdate();
    ~ControllerUpdate();
    void cityUpdate(enum Cities city);
};

enum Cities{
    sanfrancisco = "sanfrancisco",
    washington= "washington",
    newyork = "newyork",
    chicago = "chicago",
    minneapolis = "minneapolis",
    chattanooga = "chattanooga"
};
#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERUPDATE_H
