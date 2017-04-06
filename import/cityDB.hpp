#ifndef FREE_BIKE_PROJECT_REPOSITORY_CITYDB_H
#define FREE_BIKE_PROJECT_REPOSITORY_CITYDB_H
#include <iostream>
#include <string>
#include <vector>


#ifndef MAXYEARGAP
     #define MAXYEARGAP 10
#endif


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
 * The place for infos not present in the CSV file should be initialised to -1.
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
     * @brief Constructor of the class.
     * It initializes all the attributes about the informations of a city with the values taken as parameters.
     *
     * @param name name of the city.
     * @param scriptPath path to the downloading script of the city.
     * @param dirCSV path to the directory which contains the CSV files downloaded by the scripts.
     * @param dirDB path to the directory where we store the database for this city.
     * @param filesNames names of the different files we need to parse for the city.
     * @param shape describes the shape of the CSV files (which column contains which information).
     * @param minYearData first year of data we have for the city.
     * @param maxYearData the last year of data we have for the city.
     **/
    CityDB(string const name, string const scriptPath, string const dirCSV, string const dirDB,
           vector<string> * filesNames, CSVShape * shape, int minYearData, int maxYearData);
    /**
  *  @brief Destructor of the class.
  **/
    ~CityDB();
    string name;
    string scriptPath;
    string dirCSV;
    string dirDB;
    vector<string> * filesNames;
    /**
     * @var these two next attributes (maxYearData and minYearData) are giving us the info of the limits of the data we have upon time.
     */
    int maxYearData;
    int minYearData;
    CSVShape * shape;
    /**
  * @var Pointer on the database of the city.
  **/
    Database * database;
    /**
 * @var isActive is set to true if the database of the city is loaded on the memory and false if not.
 **/
    bool isActive;


    /**
     * @brief Activate the database for the city by loading it from the disk or initializing it.
     * The function will first search if the file in the directory dirCSV named city.db (with city the name of the city) exists
     * or not, if it exists it will load it and if not it wil create a new Database.
     * The new Database wil be created by first downloading the CSV files then importing each one of them to the database.
     * In each cases the attribute database will point on
     * the same database given in return value.
     * @return The pointer on the database.
     **/
    Database * activate();

    /**
     * @brief Desactivate the database of the city by saving it on the disk and deleting it from the memory.
     * The database will be savec at the dirDB place.
     **/
    void desactivate();

    /**
     * @brief Initialise the Database from the CSV files known by their directory path (dirCSV) and their names (fileNames).
     */
    void DBInstanciation();

     /**
      * @brief Import one CSV file inside the database of the class (attribute database).
      * This function is meant to be called for the first initialisation of the database, the parameters nodesStation, nodesDay etc ...
      * are here to keep a track of the initialisation of the database between the import of each different files.
      * @param file name of the file we want to import, the file must exist in the directory pointed by the dirCSV attribute.
      * @param nodesStation A vector containing pointers to station nodes. The size will be changed inside this function.
      * @param nodesDay An array of 3 dimensions which size should be nodesDay[nbyears][12][31] with nbYears = maxYearData - this->minYearData +1
      * containing pointers to day nodes (or NULL values).
      * @param nodesMonth An array of 2 dimensions which size should be nodesMonth[nbyears][12] with nbYears = maxYearData - this->minYearData +1
      * containing pointers to month nodes (or NULL values).
      * @param nodesYear An array of 1 dimension which size should be nodesYear[nbyears] with nbYears = maxYearData - this->minYearData +1
      * containing pointers to year nodes (or NULL values).
      * @param nodesMinute An array of 2 dimensions which size should be nodesMinute[24][60]
      * containing pointers to minute node (or NULL values).
      * @param nodesHour An array of 1 dimension which size should be nodesHour[24]
      * containing pointers to hour node (or NULL values).
      */
  void importOneFile(string const file, vector<Result *> nodesStation,  vector<vector<vector<Result * > > > nodesDay,
		     vector<vector<Result * > > nodesMonth,
		     vector<Result * > nodesYear,
		     vector<vector<Result * > > nodesMinute,
		     vector<Result * > nodesHour

);

    /**
     *  @brief Launch the script for downloading the csv files.
     *  The csv files are the ones whose names are stored in the attribute filesNames stored at the location dirCSV.
     */

     void download();
    /**
     * @brief Function parsing the data of a .csv file.
     * All the data is extracted in a matrix to be inserted in the database later.
     * The shape of the array is done in a way that if you do matrix[i][j] you will have the data located in the
     * column i and the line j of the csv file.
     * @param csv_file the name of the .csv file.
     *
     * @return vector<vector<string> > : a bidimensional dynamic array containing all the data of the csv_file.
     **/
    vector<vector<string> > parseCSVFile(const string &csv_file);

    /**
     * @brief Function which parses two strings to store date and time infos inside a struct dateAndTime.
     * The dateAndTime struct is allowed dynamically so a delete has to be called on the return value.
     * The shape of the strings in parameters is specified with the parameters description.
     * @param date string containing date infos (should be formated as this : month/day/year).
     * @param time string containing hour infos (should be formated as this : hour:minute).
     * @return a pointer to a dateAndTime struct which was allocated dynamically, this one has to be deleted.
     **/
     dateAndTime * dateInNodes(const string & date, const string & time);

    /**
     * @brief Creates all the entities of the database.
     * It creates the entities with the method newEntity of the database's interface.
     *
     * @param the pointer on the database.
     **/
    void entitiesCreation(Database *);

    /**
     * @brief Creates all the relationships of the database.
     * It creates the relationships with the method newRelation of the database's interface.
     *
     * @param the pointer on the database.
     **/
    void relationshipsCreation(Database *);

private :
    /**
     * @brief Search for the max value from two columns of a data matrix.
     * @param data a matrix of data from which we want to take the max from two columns.
     * @param first the first column in which we want the max.
     * @param second the second column in which we want the max.
     * @return the maximum value in the columns first and second of the data matrix.
     */
    int getMaxID(vector<vector<string> > data, int first, int second);

    /**
     * @brief Initialise a station node in the array nodesStation given in parameters and add it to the database.
     * If the place in the array where the node should be initialised is NULL it is initialised and added to the database.
     * If they are not NULL the nothing is done.
     * @param nodesStation pointer to where the  node station will be stored.
     * @param id the ID of the station.
     * @param name the name of the station.
     * @param latitude the latitude of the station.
     * @param longitude the longitude of the station.
     */
    void initialiseStationNode(Result * nodeStation, int id, string name, double latitude, double longitude);

    /**
     * @brief Initialise a date node in the pointers given in parameters and add it to the database.
     * The nodes given in parameters are used to store the new initialised nodes,
     * if those nodes are not NULL then nothing is done.
     * If the nodes have to be initialised then they are added to the database.
     * @param nodeDay where the node day should be initialised.
     * @param nodeMonth where the node month should be initialised.
     * @param nodeYear where the node year should be initialised.
     * @param year the year of the date we want to initialise (should be between minYearData et maxYearData).
     * @param month the month of the date we want to initialise.
     * @param day the day of the date we want to initialise.
     */
    void initialiseDateNode(Result * nodeDay, Result * nodeMonth, Result * nodeYear,int year, int month, int day);

    /**
     * @brief Initialise an hour node inside the pointers given in parameters and add it to the database.
     * The nodes given in parameters are used to store the new initialised node,
     * if those nodes are not NULL then nothing is done.
     * If nodeHour and nodeMinute are not NULL the they are intialised and added to the database.
     * @param nodeHour where the node hour should be initialised.
     * @param nodeMinute where the minute node should be initialised.
     * @param hour value of the hour we want to initialise.
     * @param minute value of the minute we want to initialise.
     */
    void initialiseHourNode(Result * nodeHour, Result * nodeMinute,int hour, int minute);
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CITYDB_H
