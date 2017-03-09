#ifndef GRAPHREAD_HPP
#define GRAPHREAD_HPP

#include <string>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

#include "DBTools.hpp"
//#include "Result.hpp"

using namespace tlp;

class DatabaseImpl;


class GraphRead {
  /*
  Result * getNodes(const std::string &entityName, Attribute * attr[] = NULL, int nAttr = 0) const;
  Result * getEdges(const std::string &relationName, Attribute * attr[] = NULL, int nAttr = 0) const;
  */
};


class GraphReadAbstract: public GraphRead {
protected:
  Graph * g;
  DatabaseImpl * db;

public: 
  std::vector<node> * getNodes(const std::string &entityName) const;
  std::vector<edge> * getEdges(const std::string &relationName) const;
  
protected:
  GraphReadAbstract(Graph * g, DatabaseImpl * db);
  ~GraphReadAbstract();
};


#endif //GRAPHREAD_HPP
