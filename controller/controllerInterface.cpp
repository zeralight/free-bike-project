#include "controllerInterface.hpp"
#include "mainwindow.hpp"
#include <QApplication>
#include "controller.hpp"
using namespace std;
ControllerInterface::ControllerInterface(Controller * controller):controller(controller){
    QApplication a(argc, argv);
    MW = new MainWindow(this);
    argc = 1;
    asprintf("Free bike project",&argv);
}

ControllerInterface::~ControllerInterface(){
    free(argv);

}

void ControllerInterface::runInterface() {
    window.show();
    a.exec();
}
int ControllerInterface::returnDensityFilter(bool yes=0, bool weak = 1, int percentage){

    return 1;
}

int ControllerInterface::returnPeriodFilter(int dayBegin, int monthBegin, int yearBegin, int hourBegin, int minuteBegin,
                       int dayEnd, int monthEnd, int yearEnd, int hourEnd, int minuteEnd,
                       bool normal = 1, bool slots[24]){
    return 1;
}

int ControllerInterface::returnTripsFilter(int maxLength, int minLength, int maxDensity, int minDensity){
    return 1;
}

int ControllerInterface::returnUsersFilter(bool men, bool women, int minAge, int maxAge, bool subscriber, bool nonSubscriber){

    return 1;
}

void ControllerInterface::cityChanged(const string & cityName){
    enum Cities city;
    switch (cityName){
        case "New-York" :
            city = newyork;
        case "San Francisco" :
            city = sanfrancisco;
        case "Washington" :
            city = washington;
        case "Chattanooga" :
            city = chattanooga;
        case "Chicago" :
            city = chicago;
        case "Minneapolis" :
            city = minneapolis;
    }
    controller->activateCity(city);
}