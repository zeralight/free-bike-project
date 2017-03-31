#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERUPDATE_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERUPDATE_H

#ifndef SCRIPT_FILES_DL
    #define SCRIPT_FILES_DL "../download_bike/"
#endif

#ifndef DB_DIR
    #define DB_DIR "./"
#endif
#include <wrappy/wrappy.h>
#include "controller.hpp"
#include "../import/cityDB.h"
class ControllerUpdate{
public :
    ControllerUpdate();
    ~ControllerUpdate();
    void cityUpdate(CityDB * city);
    void activate(CityDB * city);
    CityDB * chicago;
    CityDB * sanFrancisco;
    CityDB * washington;
    CityDB * newYork;
    CityDB * minneapolis;
    CityDB * chattanooga;
    CityDB * whichActive;
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
