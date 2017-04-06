#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERINTERFACE_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERINTERFACE_H

class ControllerInterface;

#include "mainwindow.hpp"
#include <QApplication>
#include "controller.hpp"

using namespace std;

class ControllerInterface
{
public:
    ControllerInterface(Controller * controller);
    ~ControllerInterface();
    MainWindow * MW;
    QApplication * application;
    int  argc;
    char ** argv;

    void runInterface();
  int returnDensityFilter(int percentage, bool yes=0, bool weak = 1);

    int returnPeriodFilter(int dayBegin, int monthBegin, int yearBegin, int hourBegin, int minuteBegin,
                           int dayEnd, int monthEnd, int yearEnd, int hourEnd, int minuteEnd,
                           bool slots[24],  bool normal = true);

    int returnTripsFilter(int maxLength, int minLength, int maxDensity, int minDensity);

    int returnUsersFilter(bool men, bool women, int minAge, int maxAge, bool subscriber, bool nonSubscriber);

    void cityChanged(const string &);
private:
    Controller * controller;
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERINTERFACE_H
