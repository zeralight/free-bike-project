#include "controllerUpdate.hpp"
#include "../import/import.hpp"

#include <wrappy/wrappy.h>

ControllerUpdate::ControllerUpdate(){}
ControllerUpdate::~ControllerUpdate(){}
void ControllerUpdate::cityUpdate(enum Cities city){
    wrappy::call(SCRIPT_FILES_DL+city+"/download_bike_"+city);
    //Maintenant il faut appeler l'import
}