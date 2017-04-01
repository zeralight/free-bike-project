#ifndef FREE_BIKE_PROJECT_REPOSITORY_CITYDB_H
#define FREE_BIKE_PROJECT_REPOSITORY_CITYDB_H
#include <iostream>
#include <string>
#include <vector>

#include "Database.hpp"
#include "DBTools.hpp"
#include "Result.hpp"

using namespace std;
/**
 * @struct This struct allows us to know in which column of the CSV files are the info we seek to use.
 **/
struct CSVShape {
    int genderPLace;
    int StationStartIDPlace;
    int StationEndIDPlace;
    int tripIDPlace;
    int tripDurationPlace;
    int userTypePlace;
    int startTimePlace;
    int endTimePlace;
    int startDatePlace;
    int endDatePlace;
};

/**
 * @class This class is meant to be initialised with all kind of informations for a city.
 **/
class CityDB {
public:
    /**
     * @fn Constructor of the class
     * It initializes all the attributes about the informations of a city with the values taken as parameters.
     *
     * @param name name of the city
     * @param scriptDir ?
     * @param dirCSV name of the directory which contains the CSV files (?)
     * @param dirDB name of the directory which contains the database (?)
     * @param filesNames file names
     * @param shape ?
     **/
    CityDB(string const& name, string const & scriptDir, string const & dirCSV, string const & dirDB,
           vector<string const&> filesNames, CSVShape * shape);
    /**
  * @fn Destructor of the class
  **/
    ~CityDB();
    string name;
    string scriptDir;
    string dirCSV;
    string dirDB;
    vector<string> filesNames;
    CSVShape * shape;
    /**
  * @var Pointer on the database containing all the information
  **/
    Database * database;
    /**
 * @var ?
 **/
    bool isActive;


    /**
     * @fn ?
     **/
    Database * activate();

    /**
     * @fn ?
     **/
    void desactivate();

    /**
  * @fn Function parsing the data of a .csv file
  * All the data is extracted in a matrix to be inserted in the database later.
  *
  * @param csv_file the name of the .csv file
  *
  * @return vector<vector<string> > : a bidimensional dynamic array containing all the data of the csv_file
  **/
    vector<vector<string> > parseCSVFile(const string &csv_file);

    //the next methods are for the initialisation of the DB.

    /**
     * @fn Function which parses a CSV date to create the nodes relating to the date later
     * The function splits the date into 5 elements (year, month, day, hour, minute)
     *
     * @param the date in its CSV format
     *
     * @return vector<int> : a dynamic array containing the 5 future nodes
     **/
    vector<int> dateInNodes(const string &);

    /**
     * @fn Creates all the entities of the database
     * It creates the entities with the method newEntity of the database's interface
     *
     * @param the pointer on the database
     **/
    void entitiesCreation(Database *);

    /**
     * @fn Creates all the relationships of the database
     * It creates the relationships with the method newRelation of the database's interface
     *
     * @param the pointer on the database
     **/
    void relationshipsCreation(Database *);
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CITYDB_H
