#include "controllerInterface.hpp"
#include "mainwindow.hpp"
#include <QApplication>
#include "controller.hpp"
using namespace std;
ControllerInterface::ControllerInterface(Controller * controller):controller(controller){
    argc = 1;
    asprintf(&argv, "Free bike project");
    application = new QApplication(argc,&argv);
MW = new MainWindow(this);
    	    }

ControllerInterface::~ControllerInterface(){
    free(argv);
    delete controller;

}

void ControllerInterface::runInterface() {
    MW->show();
    application->exec();
}
void ControllerInterface::returnDensityFilter(int percentage, bool yes, bool weak){

    return 1;
}

void ControllerInterface::returnPeriodFilter(int dayBegin, int monthBegin, int yearBegin, int hourBegin, int minuteBegin,
                       int dayEnd, int monthEnd, int yearEnd, int hourEnd, int minuteEnd,
		       bool slots[24], bool normal){
    return 1;
}

void ControllerInterface::returnTripsFilter(int maxLength, int minLength, int maxDensity, int minDensity){
    return 1;
}

void ControllerInterface::returnUsersFilter(bool men, bool women, int minAge, int maxAge, bool subscriber, bool nonSubscriber){

    return 1;
}

void ControllerInterface::cityChanged(const string & cityName){
    enum Cities city;
    if(!cityName.compare("New-York")){
	city = NEWYORK;
      }
    if(!cityName.compare("San Francisco")){
	  city = SANFRANCISCO;
	}
    if(!cityName.compare("Washington")){
            city = WASHINGTON;
	  }
    if(!cityName.compare("Chattanooga")){
      city = CHATTANOOGA;
	      }
    if(!cityName.compare("Chicago")){
            city = CHICAGO;
		}
    if(!cityName.compare("Minneapolis")){
            city = MINNEAPOLIS;
    }
    controller->activateCity(city);
}
