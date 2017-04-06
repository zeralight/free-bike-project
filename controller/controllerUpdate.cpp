#include "controllerUpdate.hpp"


#include "../import/cityDB.hpp"
#include "controller.hpp"
#include <string>
using namespace std;
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

    int minYear= 2013;
    int maxYear = 2017;
    
    vector<string> * filesChicago = new vector<string>; // à remplir
    filesChicago->push_back("");
    chicago = new CityDB(string("Chicago"),string(SCRIPT_FILES_DL)+"chicago",string(SCRIPT_FILES_DL)+"chicago",string(DB_DIR),filesChicago,shapeChicago,minYear,maxYear);
/*
    CSVShape * shapesanFrancisco= new CSVShape; //à remplir
    vector<string> * filessanFrancisco = new vector<string>; // à remplir
    sanFrancisco = new CityDB("sanFrancisco",string(SCRIPT_FILES_DL)+"sanFrancisco",string(SCRIPT_FILES_DL)+"sanFrancisco",DB_DIR,filessanFrancisco,shapesanFrancisco);

    CSVShape * shapewashington= new CSVShape; //à remplir
    vector<string> * fileswashington = new vector<string>; // à remplir
    washington = new CityDB("washington",string(SCRIPT_FILES_DL)+"washington",string(SCRIPT_FILES_DL)+"washington",DB_DIR,fileswashington,shapewashington);

    CSVShape * shapenewYork= new CSVShape; //à remplir
    vector<string> * filesnewYork = new vector<string>; // à remplir
    newYork = new CityDB("newYork",string(SCRIPT_FILES_DL)+"newYork",string(SCRIPT_FILES_DL)+"newYork",DB_DIR,filesnewYork,shapenewYork);

    CSVShape * shapeminneapolis= new CSVShape; //à remplir
    vector<string> * filesminneapolis = new vector<string>; // à remplir
    minneapolis = new CityDB("minneapolis",string(SCRIPT_FILES_DL)+"minneapolis",string(SCRIPT_FILES_DL)+"minneapolis",DB_DIR,filesminneapolis,shapeminneapolis);

    CSVShape * shapechattanooga= new CSVShape; //à remplir
    vector<string> * fileschattanooga = new vector<string>; // à remplir
    chattanooga = new CityDB("chattanooga",string(SCRIPT_FILES_DL)+"chattanooga",string(SCRIPT_FILES_DL)+"chattanooga",DB_DIR,fileschattanooga,shapechattanooga);

*/
}

void ControllerUpdate::activate(enum Cities city){
    CityDB * toActivate;
    switch(city){
        case SANFRANCISCO :
            toActivate=this->sanFrancisco;
        case MINNEAPOLIS :
            toActivate=this->minneapolis;
        case CHICAGO :
            toActivate=this->chicago;
        case CHATTANOOGA :
            toActivate=this->chattanooga;
        case NEWYORK :
            toActivate=this->newYork;
        case WASHINGTON :
            toActivate=this->washington;
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
