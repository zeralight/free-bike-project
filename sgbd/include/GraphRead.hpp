#ifndef GRAPHREAD_HPP
#define GRAPHREAD_HPP

///@cond DEV

#include <string>
#include <vector>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

#include "DBTools.hpp"
#include "Pattern.hpp"
#include "Result.hpp"

using namespace tlp;

class DatabaseImpl;
class PatternImpl;


class GraphRead {
  /**
   * @copydoc Database::match(Pattern *)
   **/
  virtual Result * match(Pattern * p) =0;
  virtual std::vector<Attribute *> * get(const std::string &label, const std::string &attributeName) const =0;  
};


class GraphReadAbstract: public GraphRead {
protected:
  Graph * g;
  DatabaseImpl * db;
  PatternImpl * pattern;
  
public:
  // /!\ ne fonctionnera pas pour une foret de graphes
  Result * match(Pattern * p);
  
  std::vector<node> * getNodes(const std::string &entityName) const;
  std::vector<edge> * getEdges(const std::string &relationName) const;

  std::vector<Attribute *> * get(const std::string &label, const std::string &attributeName) const;
  std::vector<Attribute *> * getElement(const std::string &label, const std::string &attributeName) const;
  
  Graph * getGraph();
  void setPattern(PatternImpl * pi);
  
protected:
  GraphReadAbstract(Graph * g, DatabaseImpl * db);
  virtual ~GraphReadAbstract();
};

///@endcond

#endif //GRAPHREAD_HPP
