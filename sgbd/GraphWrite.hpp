#ifndef GRAPHWRITE_HPP
#define GRAPHWRITE_HPP

#include <string>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

#include "GraphRead.hpp"
#include "DBTools.hpp"

using namespace tlp;

class DatabaseImpl;


class GraphWrite : public GraphRead {
public:
  virtual bool editNodes(const std::string &entityName, Attribute * attr[], int nAttr) =0;
  virtual bool editEdges(const std::string &relationName, Attribute * attr[], int nAttr) =0;
};


class GraphWriteAbstract: public GraphWrite, public GraphReadAbstract {
public: 
  bool editNodes(const std::string &entityName, Attribute * attr[], int nAttr);  
  bool editEdges(const std::string &relationName, Attribute * attr[], int nAttr);
  
protected:
  GraphWriteAbstract(Graph * g, DatabaseImpl * db);
  ~GraphWriteAbstract();
};


#endif //GRAPHWRITE_HPP
