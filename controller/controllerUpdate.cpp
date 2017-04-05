#include "controllerUpdate.hpp"


#include "cityDB.h"
#include "controller.hpp"

ControllerUpdate::ControllerUpdate(Controller * controller) : whichActive(NULL), controller(controller){
    CSVShape * shapeChicago= new CSVShape;
    shapeChicago->startTimePlace = 1;
    shapeChicago->startDatePlace = 1;
    shapeChicago->userTypePlace = 1;
    shapeChicago->bikeIDPlace = 1;
    shapeChicago->birthYearPlace = 1;
    shapeChicago->endDatePlace = 1;
    shapeChicago->endTimePlace = 1;
    shapeChicago->genderPlace =1;
    shapeChicago->stationEndIDPlace =1;
    shapeChicago->stationStartIDPlace = 1;
    shapeChicago->stationEndLatitudePlace=1;
    shapeChicago->stationEndLongitudePlace =1;
    shapeChicago->stationEndNamePlace =1;
    shapeChicago->userTypePlace = 1;
    shapeChicago->tripIDPlace=1;
    shapeChicago->tripDurationPlace=1;
    shapeChicago->stationStartNamePlace=1;
    shapeChicago->stationStartLongitudePlace=1;
    shapeChicago->stationStartLatitudePlace=1;

    vector<string> filesChicago = new vector<string>; // à remplir
    filesChicago.push_back("");
    chicago = new CityDB("Chicago",SCRIPT_FILES_DL+"chicago",SCRIPT_FILES_DL+"chicago",DB_DIR,filesChicago,shapeChicago);
/*
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

*/
}

void ControllerUpdate::activate(enum Cities city){
    CityDB * toActivate;
    switch(city){
        case sanfrancisco :
            toActivate=sanFrancisco;
        case minneapolis :
            toActivate=minneapolis;
        case chicago:
            toActivate=chicago;
        case chattanooga:
            toActivate=chattanooga;
        case newyork:
            toActivate=newYork;
        case washington:
            toActivate=washington;
    }
    if(whichActive != NULL){
        whichActive->desactivate();
    }
    toActivate->activate();
    whichActive = toActivate;
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