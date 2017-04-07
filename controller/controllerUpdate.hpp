#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERUPDATE_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERUPDATE_H

#ifndef SCRIPT_FILES_DL
    #define SCRIPT_FILES_DL "../download_bike/"
#endif

#ifndef DB_DIR
    #define DB_DIR "./"
#endif

class ControllerUpdate;
#include <wrappy/wrappy.h>
#include "controller.hpp"
#include "../import/cityDB.hpp"
/**
 * @brief This class is meant to deal with all the stuff related to the database of each city.
 * All the infos coming from the databases or going to the databases are passing by this class.
 */
class ControllerUpdate{
public :
    /**
    * @brief constructor of the class
    * @param controller A pointer to the class Controller which possess this class in his attributes.
    */
    ControllerUpdate(Controller * controller);
    ~ControllerUpdate();
    /**
     * @brief This method updates the data for a city.
     * If there is new data available for the city given in parameters then it download it and add it to the database.
     * @warning This method is not implemented yet so it does nothing.
     * @param city The parameters giving which city should be updated.
     */
    void cityUpdate(enum Cities city);
    /**
    * @brief This method is called a city database in memory.
    * Before loading the database in memory this method verify if there is not already one and if there is one
     * then it stores it on the disk to replace it by the database of the new city. If the city given in parameters
     * is the one which is already active then this method does nothing.
     * @param city This parameter stores the info of which city we want to activate.
    */
    void activate(enum Cities city);

    CityDB * chicago; /**< a pointer to the CityDB instance representing Chicago*/
    CityDB * sanFrancisco; /**< a pointer to the CityDB instance representing San Francisco*/
    CityDB * washington; /**< a pointer to the CityDB instance representing Washington*/
    CityDB * newYork; /**< a pointer to the CityDB instance representing New York*/
    CityDB * minneapolis; /**< a pointer to the CityDB instance representing Minneapolis*/
    CityDB * chattanooga; /**< a pointer to the CityDB instance representing Chattanooga*/
    CityDB * whichActive; /**< a pointer to the CityDB instance whose database is currently stored in the ram memory*/
private:
    Controller * controller;
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERUPDATE_H
