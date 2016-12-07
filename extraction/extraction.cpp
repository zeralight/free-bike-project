#include <iostream>
#include <string>
#include <vector> // Multidimensional arrays library
#include <fstream> // Files library

using namespace std;

vector<vector<string> > parseCSVFile(char* csv_file)
{
  ifstream file(csv_file, ios::in);
  if (file)
    {
      vector<string> namesVarList;
      char character;
      int i=0;
      while ( character != '\n' && file.get(character) )
	{
	  namesVarList.push_back("");
	  while ( character != ',' && character != '\n' )
	    {
	      namesVarList[i] += character;
	      file.get(character);
	    }
	  i++;
	}
      vector<vector<string> > data;
      for (int j=0; j<i; j++)
	{
	  data.push_back(vector<string>(1, namesVarList[j]));
	}
      i=0; int j=1; character='\0';
      while ( !file.eof() && file.get(character) )
	{
	  data[i].push_back("");
	  while ( character != ',' && character != '\n' )
	    {
	      data[i][j] += character;
	      file.get(character);
	    }
	  if ( character == ',' )
	    {
	      i++;
	    }
	  if ( character == '\n' )
	    {
	      i=0;
	      j++;
	    }
	}
      return data;
    }
  else
    {
      cerr << "Error: can't open file" << endl;
      vector<vector<string> > empty;
      return empty;
    }
}

