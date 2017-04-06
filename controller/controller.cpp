#include "controller.hpp"
#include "controllerInterface.hpp"
#include "controllerUpdate.hpp"
#include "controllerOSM.hpp"
Controller::Controller() : cI(new ControllerInterface(this)), cU(new ControllerUpdate(this)),cOSM(new ControllerOSM(this)) {

}

Controller::~Controller() {
    delete cU;
    delete cOSM;
    delete cI;
}

void Controller::activateCity(enum Cities city){
    cU->activate(city);
}

void Controller::runInterface(){
  cI->runInterface();
}
