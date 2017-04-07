#include "controllerUpdate.hpp"


#include "../import/cityDB.hpp"
#include "controller.hpp"
#include <string>
using namespace std;
ControllerUpdate::ControllerUpdate(Controller * controller) : whichActive(NULL), controller(controller){
    /* 2 fichiers .csv
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
*/


    /* plusieur fichier .csv
    CSVShape * shapesanFrancisco= new CSVShape;
    shapesanFrancisco->startTimePlace = ;
    shapesanFrancisco->startDatePlace = ;
    shapesanFrancisco->userTypePlace = ;
    shapesanFrancisco->bikeIDPlace = ;
    shapesanFrancisco->birthYearPlace = ;
    shapesanFrancisco->endDatePlace = ;
    shapesanFrancisco->endTimePlace = ;
    shapesanFrancisco->genderPlace =;
    shapesanFrancisco->stationEndIDPlace =;
    shapesanFrancisco->stationStartIDPlace = ;
    shapesanFrancisco->stationEndLatitudePlace=;
    shapesanFrancisco->stationEndLongitudePlace =;
    shapesanFrancisco->stationEndNamePlace =;
    shapesanFrancisco->tripIDPlace=;
    shapesanFrancisco->tripDurationPlace=;
    shapesanFrancisco->stationStartNamePlace=;
    shapesanFrancisco->stationStartLongitudePlace=;
    shapesanFrancisco->stationStartLatitudePlace=;
    int minYear= 2013;
    int maxYear = 2016;
    vector<string> * filessanFrancisco = new vector<string>; // à remplir
    sanFrancisco = new CityDB("sanFrancisco",string(SCRIPT_FILES_DL)+"sanFrancisco",string(SCRIPT_FILES_DL)+"sanFrancisco",DB_DIR,filessanFrancisco,shapesanFrancisco,minYear,maxYear);
    */

    /* 2 fichiers  .csv
   CSVShape * shapeminneapolis= new CSVShape;
   shapeminneapolis->startTimePlace = ;
   shapeminneapolis->startDatePlace = ;
   shapeminneapolis->userTypePlace = ;
   shapeminneapolis->bikeIDPlace = ;
   shapeminneapolis->birthYearPlace = ;
   shapeminneapolis->endDatePlace = ;
   shapeminneapolis->endTimePlace = ;
   shapeminneapolis->genderPlace =;
   shapeminneapolis->stationEndIDPlace =;
   shapeminneapolis->stationStartIDPlace = ;
   shapeminneapolis->stationEndLatitudePlace=;
   shapeminneapolis->stationEndLongitudePlace =;
   shapeminneapolis->stationEndNamePlace =;
   shapeminneapolis->tripIDPlace=;
   shapeminneapolis->tripDurationPlace=;
   shapeminneapolis->stationStartNamePlace=;
   shapeminneapolis->stationStartLongitudePlace=;
   shapeminneapolis->stationStartLatitudePlace=;
   int minYear=;
   int maxYear =;
   vector<string> * filesminneapolis = new vector<string>; // à remplir
   minneapolis = new CityDB("minneapolis",string(SCRIPT_FILES_DL)+"minneapolis",string(SCRIPT_FILES_DL)+"minneapolis",DB_DIR,filesminneapolis,shapeminneapolis,minYear,maxYear);
   */


    CSVShape * shapewashington= new CSVShape;
    shapewashington->startTimePlace = 2;
    shapewashington->startDatePlace = 2;
    shapewashington->userTypePlace = 9;
    shapewashington->bikeIDPlace = 8;
    shapewashington->birthYearPlace = -1;
    shapewashington->endDatePlace = 3;
    shapewashington->endTimePlace = 3;
    shapewashington->genderPlace =-1;
    shapewashington->stationEndIDPlace =6;
    shapewashington->stationStartIDPlace = 4;
    shapewashington->stationEndLatitudePlace=-1;
    shapewashington->stationEndLongitudePlace =-1;
    shapewashington->stationEndNamePlace =7;
    shapewashington->tripIDPlace=-1;
    shapewashington->tripDurationPlace=1;
    shapewashington->stationStartNamePlace=5;
    shapewashington->stationStartLongitudePlace=-1;
    shapewashington->stationStartLatitudePlace=-1;
    int minYear= 2010;
    int maxYear = 2016;
    vector<string> * fileswashington = new vector<string>;
    fileswashington->push_back("2010-Q4-cabi-trip-history-data.csv");

    fileswashington->push_back("2011-Q1-cabi-trip-history-data.csv");
    fileswashington->push_back("2011-Q2-cabi-trip-history-data.csv");
    fileswashington->push_back("2011-Q3-cabi-trip-history-data.csv");
    fileswashington->push_back("2011-Q4-cabi-trip-history-data.csv");

    fileswashington->push_back("2012-Q1-cabi-trip-history-data.csv");
    fileswashington->push_back("2012-Q2-cabi-trip-history-data.csv");
    fileswashington->push_back("2012-Q3-cabi-trip-history-data.csv");
    fileswashington->push_back("2012-Q4-cabi-trip-history-data.csv");

    fileswashington->push_back("2013-Q1-cabi-trip-history-data.csv");
    fileswashington->push_back("2013-Q2-cabi-trip-history-data.csv");
    fileswashington->push_back("2013-Q3-cabi-trip-history-data.csv");
    fileswashington->push_back("2013-Q4-cabi-trip-history-data.csv");

    fileswashington->push_back("2014-Q1-cabi-trip-history-data.csv");
    fileswashington->push_back("2014-Q2-cabi-trip-history-data.csv");
    fileswashington->push_back("2014-Q3-cabi-trip-history-data.csv");
    fileswashington->push_back("2014-Q4-cabi-trip-history-data.csv");

    fileswashington->push_back("2015-Q1-Trips-History-Data.csv");
    fileswashington->push_back("2015-Q2-Trips-History-Data.csv");
    fileswashington->push_back("2015-Q3-cabi-trip-history-data.csv");
    fileswashington->push_back("2015-Q4-Trips-History-Data.csv");

    fileswashington->push_back("2016-Q1-Trips-History-Data.csv");
    fileswashington->push_back("2016-Q2-Trips-History-Data.csv");
    fileswashington->push_back("2016-Q3-Trips-History-Data-1.csv");
    fileswashington->push_back("2016-Q3-Trips-History-Data-2.csv");
    fileswashington->push_back("2016-Q4-Trips-History-Data.csv");

    washington = new CityDB("washington",string(SCRIPT_FILES_DL)+"washington",string(SCRIPT_FILES_DL)+"washington",DB_DIR,fileswashington,shapewashington,minYear,maxYear);




    CSVShape * shapenewYork= new CSVShape;
    shapenewYork->startTimePlace = 2;
    shapenewYork->startDatePlace = 2;
    shapenewYork->userTypePlace = 13;
    shapenewYork->bikeIDPlace = 12;
    shapenewYork->birthYearPlace = 14;
    shapenewYork->endDatePlace = 3;
    shapenewYork->endTimePlace = 3;
    shapenewYork->genderPlace =15;
    shapenewYork->stationEndIDPlace =8;
    shapenewYork->stationStartIDPlace = 4;
    shapenewYork->stationEndLatitudePlace=10;
    shapenewYork->stationEndLongitudePlace =11;
    shapenewYork->stationEndNamePlace =9;
    shapenewYork->tripIDPlace=-1;
    shapenewYork->tripDurationPlace=1;
    shapenewYork->stationStartNamePlace=5;
    shapenewYork->stationStartLongitudePlace=7;
    shapenewYork->stationStartLatitudePlace=6;
    int minYear= 2013;
    int maxYear = 2016;
    vector<string> * filesnewYork = new vector<string>;
    filesnewYork->push_back("2013-07 - Citi Bike trip data.csv");
    filesnewYork->push_back("2013-08 - Citi Bike trip data.csv");
    filesnewYork->push_back("2013-09 - Citi Bike trip data.csv");
    filesnewYork->push_back("2013-10 - Citi Bike trip data.csv");
    filesnewYork->push_back("2013-11 - Citi Bike trip data.csv");
    filesnewYork->push_back("2013-12 - Citi Bike trip data.csv");
    filesnewYork->push_back("2014-01 - Citi Bike trip data.csv");
    filesnewYork->push_back("2014-02 - Citi Bike trip data.csv");
    filesnewYork->push_back("2014-03 - Citi Bike trip data.csv");
    filesnewYork->push_back("2014-04 - Citi Bike trip data.csv");
    filesnewYork->push_back("2014-05 - Citi Bike trip data.csv");
    filesnewYork->push_back("2014-06 - Citi Bike trip data.csv");
    filesnewYork->push_back("2014-07 - Citi Bike trip data.csv");
    filesnewYork->push_back("2014-08 - Citi Bike trip data.csv");
    filesnewYork->push_back("201409-citibike-tripdata.csv");
    filesnewYork->push_back("201410-citibike-tripdata.csv");
    filesnewYork->push_back("201411-citibike-tripdata.csv");
    filesnewYork->push_back("201412-citibike-tripdata.csv");
    filesnewYork->push_back("201501-citibike-tripdata.csv");
    filesnewYork->push_back("201502-citibike-tripdata.csv");
    filesnewYork->push_back("201503-citibike-tripdata.csv");
    filesnewYork->push_back("201504-citibike-tripdata.csv");
    filesnewYork->push_back("201505-citibike-tripdata.csv");
    filesnewYork->push_back("201506-citibike-tripdata.csv");
    filesnewYork->push_back("201507-citibike-tripdata.csv");
    filesnewYork->push_back("201508-citibike-tripdata.csv");
    filesnewYork->push_back("201509-citibike-tripdata.csv");
    filesnewYork->push_back("201510-citibike-tripdata.csv");
    filesnewYork->push_back("201511-citibike-tripdata.csv");
    filesnewYork->push_back("201512-citibike-tripdata.csv");
    filesnewYork->push_back("201601-citibike-tripdata.csv");
    filesnewYork->push_back("201602-citibike-tripdata.csv");
    filesnewYork->push_back("201603-citibike-tripdata.csv");
    filesnewYork->push_back("201604-citibike-tripdata.csv");
    filesnewYork->push_back("201605-citibike-tripdata.csv");
    filesnewYork->push_back("201606-citibike-tripdata.csv");
    filesnewYork->push_back("201607-citibike-tripdata.csv");
    filesnewYork->push_back("201608-citibike-tripdata.csv");
    filesnewYork->push_back("201609-citibike-tripdata.csv");
    filesnewYork->push_back("201610-citibike-tripdata.csv");
    filesnewYork->push_back("201611-citibike-tripdata.csv");
    filesnewYork->push_back("201612-citibike-tripdata.csv");




    newYork = new CityDB("newYork",string(SCRIPT_FILES_DL)+"newYork",string(SCRIPT_FILES_DL)+"newYork",DB_DIR,filesnewYork,shapenewYork,minYear,maxYear);


    CSVShape * shapechattanooga= new CSVShape;
    shapechattanooga->startTimePlace = 7;
    shapechattanooga->startDatePlace = 6;
    shapechattanooga->userTypePlace = 1;
    shapechattanooga->bikeIDPlace = 3;
    shapechattanooga->birthYearPlace =-1;
    shapechattanooga->endDatePlace = 12;
    shapechattanooga->endTimePlace = 13;
    shapechattanooga->genderPlace =-1;
    shapechattanooga->stationEndIDPlace =15;
    shapechattanooga->stationStartIDPlace = 9;
    shapechattanooga->stationEndLatitudePlace=-1;
    shapechattanooga->stationEndLongitudePlace =-1;
    shapechattanooga->stationEndNamePlace =14;
    shapechattanooga->tripIDPlace=-1;
    shapechattanooga->tripDurationPlace=2;
    shapechattanooga->stationStartNamePlace=8;
    shapechattanooga->stationStartLongitudePlace=-1;
    shapechattanooga->stationStartLatitudePlace=-1;
    int minYear= 2012;
    int maxYear = 2015;
    vector<string> * fileschattanooga = new vector<string>;
    fileschattanooga->push_back("Bike_Chattanooga_Trip_Data.csv");
    chattanooga = new CityDB("chattanooga",string(SCRIPT_FILES_DL)+"chattanooga",string(SCRIPT_FILES_DL)+"chattanooga",DB_DIR,fileschattanooga,shapechattanooga,minYear,maxYear);


}

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
    //Mise à jour d'une ville non fonctionnelle
}
