#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERINTERFACE_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERINTERFACE_H

class ControllerInterface;

#include "mainwindow.hpp"
#include <QApplication>
#include "controller.hpp"

using namespace std;
/**
 * @brief This class is meant to deal with all the stuff related to the interface.
 * All the infos coming from the interface or going to the interface are passing by this class.
 */
class ControllerInterface
{
public:
    /**
     * @brief constructor of the class
     * @param controller A pointer to the class Controller which possess this class in his attributes.
     */
    ControllerInterface(Controller * controller);
    ~ControllerInterface();
    MainWindow * MW; /**< a pointer the MainWindow class which is the main window of the interface*/
private:
    QApplication * application; /**< Some unclear stuff the Qt needs to run the interface correctly, so this one has to be initialised before anything about Qt is done */
    int  argc;
    char * argv;
public:
    /**
     * @brief Launches the interface.
     * This method is called to show the main window to the user.
     *  So that he can interact with it.
     */
    void runInterface();
    /**
     * @brief This method is to deal with the return values of the density filter.
     * This method is called when the density filter of the interface is validated by the user to
     * launch the required requests on the database.
     * @warning This method is not implemented yet so it does nothing.
     * @param percentage value percentage given in the density filter survey.
     * @param yes value given in the density filter survey.
     * @param weak Boolean given in the density filter survey expressing if the percentage
     * is the percentage of the weaker trips on the stronger ones.
     */
    void returnDensityFilter(int percentage, bool yes=0, bool weak = 1);

    /**
     * @brief This method is to deal with the return values of the period filter.
     * This method is called when the period filter of the interface is validated by the user to
     * launch the required requests on the database.
     * @warning This method is not implemented yet so it does nothing.
     * @param dayBegin Parameter given in the survey. Giving us the first day of a time filter.
     * @param monthBegin Parameter given in the survey. Giving us the first month of a time filter.
     * @param yearBegin Parameter given in the survey. Giving us the first year of a time filter.
     * @param hourBegin Parameter given in the survey. Giving us the first hour of a time filter.
     * @param minuteBegin Parameter given in the survey. Giving us the first minute of a time filter.
     * @param dayEnd Parameter given in the survey. Giving us the last day of a time filter.
     * @param monthEnd Parameter given in the survey. Giving us the last month of a time filter.
     * @param yearEnd Parameter given in the survey. Giving us the last month of a time filter.
     * @param hourEnd Parameter given in the survey. Giving us the last hour of a time filter.
     * @param minuteEnd Parameter given in the survey. Giving us the last minute of a time filter.
     * @param slots Parameter given in the survey. Giving us wich hours are meant to be considered if the normal parameter is set to false.
     * @param normal Parameter given in the survey. Informing us if we have to use the slots parameter or not.
     */
    void returnPeriodFilter(int dayBegin, int monthBegin, int yearBegin, int hourBegin, int minuteBegin,
                           int dayEnd, int monthEnd, int yearEnd, int hourEnd, int minuteEnd,
                           bool slots[24],  bool normal = true);

    /**
     * @brief This method is to deal with the return values of the trips filter.
     * This method is called when the trips filter of the interface is validated by the user to
     * launch the required requests on the database.
     * @warning This method is not implemented yet so it does nothing.
     * @param maxLength Parameter given in the survey. Giving us the max length of the trips we have to consider.
     * @param minLength Parameter given in the survey. Giving us the min length of the trips we have to consider.
     * @param maxDensity Parameter given in the survey. Giving us the max density of the trips we have to consider.
     * @param minDensity Parameter given in the survey. Giving us the max density of the trips we have to consider.
     */
    void returnTripsFilter(int maxLength, int minLength, int maxDensity, int minDensity);

    /**
     * @brief This method is to deal with the return values of the users filter.
     * This method is called when the users filter of the interface is validated by the user to
     * launch the required requests on the database.
     * @warning This method is not implemented yet so it does nothing.
     * @param men Parameter given in the survey. True means men should be considered, False they should not.
     * @param women Parameter given in the survey. True means women should be considered, False they should not.
     * @param minAge Parameter given in the survey. The minimum age of the users we are considering.
     * @param maxAge Parameter given in the survey. The maximum age of the users we are considering.
     * @param subscriber Parameter given in the survey. True means subscribers should be considered, False they should not.
     * @param nonSubscriber Parameter given in the survey. True means non subscribers should be considered, False they should not.
     */
    void returnUsersFilter(bool men, bool women, int minAge, int maxAge, bool subscriber, bool nonSubscriber);

    /**
     * @brief This method is called when the user changed the current city.
     * When a user changes the city in use this method is called to bring back
     * the info to the Controller so that he could activate and desactivate
     * the right databases using an other controller.
     * @param cityName The name of the city the user chose as it is shown on the interface.
     */
    void cityChanged(const string & cityName);
private:
    Controller * controller;
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERINTERFACE_H
