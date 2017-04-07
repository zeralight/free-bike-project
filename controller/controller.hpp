#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H

class Controller;

/**
 * @brief This enum defines all the cities our software is dealing with.
 */
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

/**
 * @brief This class is root class of the project.
 * This class is the main class, it means that each exchange between different parts of the project
 * for example from the interface to the database) is using this class as an intermediary.
 */
class Controller
{
public:
    Controller();
    ~Controller();
    ControllerInterface * cI; /**< a pointer the controller dealing with the interface*/
    ControllerUpdate * cU; /**< a pointer the controller dealing with the cities and their database*/
    ControllerOSM * cOSM; /**< a pointer the controller dealing with the OSM data*/
   /**
    * @brief This method is calling the right method to load a city in memory.
    * The method is calling the right method in the ControllerUpdate class to replace the database
    * inside the memory (if there is already one) by the database of the city.
    * @param city This parameter stores the info of which city we want to activate.
    */
    void activateCity(enum Cities city);
    /**
     * @brief Launches the window of the interface.
     * This method is used only one time during the project to show the window to the user.
     */
    void runInterface();
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLER_H
