#ifndef GRAPHWRITE_HPP
#define GRAPHWRITE_HPP

#include <string>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

#include "GraphRead.hpp"
#include "DBTools.hpp"

using namespace tlp;

class PatternImpl;
class DatabaseImpl;


class GraphWrite  {
public:
  virtual bool editNodes(const std::string &entityName, Attribute * attr[], int nAttr) =0;
  virtual bool editEdges(const std::string &relationName, Attribute * attr[], int nAttr) =0;
  
  /*
  virtual bool edit(Attribute * attr[], int nAttr) =0;

  bool delNodes(const std::string &entityName, Attribute * attr[] = NULL, int nAttr = 0);
  bool delEdges(const std::string &relationName, Attribute * attr[] = NULL, int nAttr = 0);
  // delete Result from database : call to destructor
  bool del();
  */
};


class GraphWriteAbstract: public GraphWrite, public GraphReadAbstract {
private:
  PatternImpl * pattern;
public: 
  bool editNodes(const std::string &entityName, Attribute * attr[], int nAttr);  
  bool editEdges(const std::string &relationName, Attribute * attr[], int nAttr);

protected:
  GraphWriteAbstract(Graph * g, DatabaseImpl * db);
  ~GraphWriteAbstract();
};


#endif //GRAPHWRITE_HPP
