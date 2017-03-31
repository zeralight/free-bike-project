#ifndef FREE_BIKE_PROJECT_REPOSITORY_CITYDB_H
#define FREE_BIKE_PROJECT_REPOSITORY_CITYDB_H
#include <iostream>
#include <string>
#include <vector>

#include "Database.hpp"
#include "DBTools.hpp"
#include "Result.hpp"

using namespace std;
/*
 * This struct allows us to know in wich column of the CSV files are the info we seek to use.
 */
struct CSVShape{
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

/*
 * This class is meant to be initialised with all kind of informations for a city.
 */
class CityDB
{
public:
    CityDB(string const& name, string const & scriptDir, string const & dirCSV, string const & dirDB,
           vector<string const&> filesNames, CSVShape * shape);
    ~CityDB();
    string name;
    string scriptDir;
    string dirCSV;
    string dirDB;
    vector<string> filesNames;
    CSVShape * shape;
    Database * database;

    vector<vector<string> > parseCSVFile(const string &csv_file);

    //the next methods are for the initialisation of the DB.
    vector<int> dateInNodes(const string &);
    void entitiesCreation(Database *);
    void relationshipsCreation(Database *);
};

#endif //FREE_BIKE_PROJECT_REPOSITORY_CITYDB_H
