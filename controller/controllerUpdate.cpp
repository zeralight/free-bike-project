#include "controllerUpdate.hpp"
#include "../import/import.hpp"

#include "../import/cityDB.h"


ControllerUpdate::ControllerUpdate() : whichActive(NULL){
    CSVShape * shapeChicago= new CSVShape; //à remplir
    vector<string> filesChicago = new vector<string>; // à remplir
    chicago = new CityDB("Chicago",SCRIPT_FILES_DL+"chicago",SCRIPT_FILES_DL+"chicago",DB_DIR,filesChicago,shapeChicago);

    CSVShape * shapesanFrancisco= new CSVShape; //à remplir
    vector<string> filessanFrancisco = new vector<string>; // à remplir
    sanFrancisco = new CityDB("sanFrancisco",SCRIPT_FILES_DL+"sanFrancisco",SCRIPT_FILES_DL+"sanFrancisco",DB_DIR,filessanFrancisco,shapesanFrancisco);

    CSVShape * shapewashington= new CSVShape; //à remplir
    vector<string> fileswashington = new vector<string>; // à remplir
    washington = new CityDB("washington",SCRIPT_FILES_DL+"washington",SCRIPT_FILES_DL+"washington",DB_DIR,fileswashington,shapewashington);

    CSVShape * shapenewYork= new CSVShape; //à remplir
    vector<string> filesnewYork = new vector<string>; // à remplir
    newYork = new CityDB("newYork",SCRIPT_FILES_DL+"newYork",SCRIPT_FILES_DL+"newYork",DB_DIR,filesnewYork,shapenewYork);

    CSVShape * shapeminneapolis= new CSVShape; //à remplir
    vector<string> filesminneapolis = new vector<string>; // à remplir
    minneapolis = new CityDB("minneapolis",SCRIPT_FILES_DL+"minneapolis",SCRIPT_FILES_DL+"minneapolis",DB_DIR,filesminneapolis,shapeminneapolis);

    CSVShape * shapechattanooga= new CSVShape; //à remplir
    vector<string> fileschattanooga = new vector<string>; // à remplir
    chattanooga = new CityDB("chattanooga",SCRIPT_FILES_DL+"chattanooga",SCRIPT_FILES_DL+"chattanooga",DB_DIR,fileschattanooga,shapechattanooga);


}

void ControllerUpdate::activate(CityDB * city){
    if(whichActive != NULL){
        whichActive->desactivate();
    }
    city->activate();
    whichActive = city;
}

ControllerUpdate::~ControllerUpdate(){
    delete chicago;
    delete minneapolis;
    delete sanFrancisco;
    delete newYork;
    delete washington;
    delete chattanooga;
}

void ControllerUpdate::cityUpdate(enum Cities city){
    //Maintenant il faut appeler l'import
}