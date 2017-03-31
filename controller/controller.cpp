#include "controller.hpp"
#include "controllerInterface.hpp"
#include "controllerUpdate.hpp"
#include "controllerOSM.hpp"
Controller::Controller() : cI(new ControllerInterface), cDB(new ControllerDB), cU(new ControllerUpdate),cOSM(new ControllerOSM) {

}

Controller::~Controller() {
    delete cU;
    delete cOSM;
    delete cI;
    delete cDB;
}