#ifndef GRAPHREAD_HPP
#define GRAPHREAD_HPP

#include <string>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

#include "DBTools.hpp"

using namespace tlp;

class DatabaseImpl;


class GraphRead {
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
