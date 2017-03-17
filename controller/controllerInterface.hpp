//
// Created by leo on 16/03/2017.
//
#ifndef FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERINTERFACE_H
#define FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERINTERFACE_H

#include "../interface/PFA/mainwindow.hpp"
#include <QApplication>
class ControllerInterface
{
public:
    ControllerInterface();
    ~ControllerInterface();
    MainWindow * MW;
    QApplication * application;
    int argc;
    char * argv;

    void runInterface();
    int returnDensityFilter(bool yes=0, bool weak = 1, int percentage);

    int returnPeriodFilter(int dayBegin, int monthBegin, int yearBegin, int hourBegin, int minuteBegin,
                           int dayEnd, int monthEnd, int yearEnd, int hourEnd, int minuteEnd,
                           bool normal = 1, bool slots[24]);

    int returnTripsFilter(int maxLength, int minLength, int maxDensity, int minDensity);

    int returnUsersFilter(bool men, bool women, int minAge, int maxAge, bool subscriber, bool nonSubscriber);
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CONTROLLERINTERFACE_H
