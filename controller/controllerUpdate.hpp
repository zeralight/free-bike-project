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
    ControllerUpdate(Controller * controller);
    ~ControllerUpdate();
    void cityUpdate(CityDB * city);
    void activate(enum Cities city);
    CityDB * chicago;
    CityDB * sanFrancisco;
    CityDB * washington;
    CityDB * newYork;
    CityDB * minneapolis;
    CityDB * chattanooga;
    CityDB * whichActive;
private:
    Controller * controller;
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERUPDATE_H
