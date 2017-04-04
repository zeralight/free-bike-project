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
 * @struct This struct allows us to store informations about date and time.
 */
struct dateAndTime{
    int minute;
    int hour;
    int day;
    int month;
    int year;
};
/**
 * @struct This struct allows us to know in which column of the CSV files are the info we seek to use.
 **/
struct CSVShape {
    int stationStartIDPlace;
    int stationEndIDPlace;
    int stationStartNamePlace;
    int stationEndNamePlace;
    int stationStartLatitudePlace;
    int stationStartLongitudePlace;
    int stationEndLatitudePlace;
    int stationEndLongitudePlace;
    int tripIDPlace;
    int tripDurationPlace;
    int userTypePlace;
    int startTimePlace;
    int endTimePlace;
    int startDatePlace;
    int endDatePlace;
    int genderPlace;
    int birthYearPlace;
    int bikeIDPlace;
};

enum values_gender {
    GENDER_MALE,
    GENDER_FEMALE,
    GENDER_NO_INFO,
};

enum values_type {
    TYPE_CUSTOMER,
    TYPE_SUBSCRIBER,
    TYPE_NO_INFO
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
     * @param scriptPath path to the downloading script of the city
     * @param dirCSV path to the directory which contains the CSV files downloaded by the scripts
     * @param dirDB path to the directory where we store the database for this city
     * @param filesNames names of the different files we need to parse for the city
     * @param shape describes the shape of the CSV files (which column contains which information)
     * @param minYearData first year of data we have for the city
     * @param maxYearData the last year of data we have for the city
     **/
    CityDB(string const& name, string const & scriptPath, string const & dirCSV, string const & dirDB,
           vector<string const&> filesNames, CSVShape * shape, int minYearData, int maxYearData);
    /**
  * @fn Destructor of the class
  **/
    ~CityDB();
    string name;
    string scriptPath;
    string dirCSV;
    string dirDB;
    vector<string> filesNames;
    /**
     * @var these two next attributes (maxYearData and minYearData) are giving us the info of the limits of the data we have upon time
     */
    int maxYearData;
    int minYearData;
    CSVShape * shape;
    /**
  * @var Pointer on the database of the city
  **/
    Database * database;
    /**
 * @var isActive is set to true if the database of the city is loaded on the memory and false if not
 **/
    bool isActive;


    /**
     * @fn Activate the database for the city by loading it from the disk or initializing it.
     * @return The pointer on the databse
     **/
    Database * activate();

    /**
     * @fn Desactivate the database of the city by saving it on the disk and deleting it from the memory
     **/
    void desactivate();

    /**
     * @fn Initialise the Database from the CSV files known by their directory path (dirCSV) and their names (fileNames)
     */
    void DBInstanciation();

    /**
     * @fn Import one CSV file inside the database of the class (attribute database)
     * @param file name of the file we want to import, the file must exist in the directory pointed by the dirCSV attribute
     */
    void importOneFile(string const & file);

    /**
     * @fn Launch the script for downloading the csv files
     */

     void download();
    /**
  * @fn Function parsing the data of a .csv file
  * All the data is extracted in a matrix to be inserted in the database later.
  *
  * @param csv_file the name of the .csv file
  *
  * @return vector<vector<string> > : a bidimensional dynamic array containing all the data of the csv_file
  **/
    vector<vector<string> > parseCSVFile(const string &csv_file);

    /**
     * @fn Function which parses two strings to store date and time infos inside a struct dateAndTime.
     * The dateAndTime struct is allowed dynamically so a delete has to be called on the return value.
     *
     * @param date string containing date infos (should be formated as this : month/day/year)
     * @param time string containing hour infos (should be formated as this : hour:minute)
     * @return a pointer to a dateAndTime struct which was allocated dynamically, this one has to be deleted
     **/
     dateAndTime * dateInNodes(const string & date, const string & time);

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

private :
    /**
     * @fn Search for the max value from two columns of a data matrix
     * @param data a matrix of data from which we want to take the max from two columns
     * @param first the first column in which we want the max
     * @param second the second column in which we want the max
     * @return the maximum value in the columns first and second of the data matrix
     */
    int getMaxID(vector<vector<string> > data, int first, int second);

    /**
     * @fn initialise a node station in the array nodesStation with given in parameters and add it to the database
     * (if the node doesn't already exist)
     * @param nodesStation the array in which the initialised node station will be stored
     * @param id the ID of the station
     * @param name the name of the station
     * @param latitude the latitude of the station
     * @param longitude the longitude of the station
     */
    void initialiseStationNode(Result ** nodesStation, int id, string name, double latitude, double longitude);

    /**
     * @fn initialise a date node in the pointers given in parameters and add it to the database
     * (if the node doesn't already exist)
     * @param nodeDay where the node day should be initialised
     * @param nodeMonth where the node month should be initialised
     * @param nodeYear where the node year should be initialised
     * @param year the year of the date we want to initialise (should be between minYearData et maxYearData)
     * @param month the month of the date we want to initialise
     * @param day the day of the date we want to initialise
     */
    void initialiseDateNode(Result * nodeDay, Result * nodeMonth, Result * nodeYear,int year, int month, int day);

    /**
     * @fn initialise an hour node inside the pointers given in parameters and add it to the database
     * (if the node doesn't already exist)
     * @param nodeHour where the node hour should be initialised
     * @param nodeMinute where the minute node should be initialised
     * @param hour value of the hour we want to initialise
     * @param minute value of the minute we want to initialise
     */
    void initialiseHourNode(Result * nodeHour, Result * nodeMinute,int hour, int minute);
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CITYDB_H
