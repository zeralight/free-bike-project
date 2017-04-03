#include <iostream>
#include <string>
#include <vector> // Multidimensional arrays library
#include <fstream> // Files library

#include <extraction.hpp>

using namespace std;

// csv_file : file name
vector<vector<string> > parseCSVFile(const string &csv_file) {
  ifstream file(csv_file, ios::in); // Read-only .csv file opening
  if (file) // If the opening succeeded
    {
      vector<string> namesVarList; // Dynamic array declaration
      char character; // Last character read
      int i=0;
      while ( character != '\n' && file.get(character) ) // While it is the 1st line
	{
	  namesVarList.push_back(""); // Creates a field
	  while ( character != ',' && character != '\n' ) // While it is the 1st line and the same field
	    {
	      namesVarList[i] += character; // Continues to write the field name
	      file.get(character); // Reads the next character
	    }
	  i++;
	}
      vector<vector<string> > data; // Dynamic bidimensional array for data
      for (int j=0; j<i; ++j)
	{
	  data.push_back(vector<string>(1, namesVarList[j])); // Creates as columns as fields in the table
	}
      i=0; int j=1; character='\0'; // '\0' to avoid a falsifying '\n'
      while (j < 10000 && !file.eof() && file.get(character) ) // While it's not the end of the file
	{
	  data[i].push_back(""); // Creates a value
	  while (character != ',' && character != '\n' ) // While it is the same line and the same value
	    {
	      data[i][j] += character; // Continues to write the value
	      file.get(character); // Reads the next character
	    }
	  if ( character == ',' ) // Manages the counters
	    {
	      i++;
	    }
	  if ( character == '\n' )
	    {
	      i=0;
	      j++;
	    }
	}
      return data; // Returns the table
    }
  else
    {
      cerr << "Error: can't open file" << endl;
      vector<vector<string> > empty; // Creates an empty dynamic bidimensional array...
      return empty; // ... to respect the type
    }
}

