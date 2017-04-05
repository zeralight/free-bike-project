#ifndef RESULTIMPL_HPP
#define RESULTIMPL_HPP

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>

#ifndef DATABASE_HPP
#include "Database.hpp"
#include "DatabaseImpl.hpp"
#include "Entity.hpp"
#include "Relation.hpp"
#endif //DATABASE_HPP

#include "GraphWrite.hpp"
#include "Result.hpp"

class DatabaseImpl;


class ResultImpl : public GraphWriteAbstract, public Result {
  //  using GraphWriteAbstract::editNodes;
  //using GraphWriteAbstract::editEdges;
  
public:
  ResultImpl(const std::string &name, Graph * g, DatabaseImpl * db);
  ~ResultImpl();
  
  // opérations sur le edge vraiment utile ?
  //temporaire doit bouger dans la hiérarchie d'héritage
  Iterator<node> * getNodes() const;
  Iterator<edge> * getEdges() const;
  
  bool editNodes(const std::string &entityName, Attribute * attr[], int nAttr);
  bool editEdges(const std::string &relationName, Attribute * attr[], int nAttr);
  void filterNodes(std::string entityName, Attribute * attr[], int nAttr, int cmpOp);
  void filterEdges(std::string relationName, Attribute * attr[], int nAttr, int cmpOp);
  void where(std::string label, Attribute * attr[], int nAttr, int cmpOp);
  std::vector<Attribute*> get(std::string labelPattern, std::string attributeName);
  
  // Plus haut dans la hiérarchie ?
  void addNode(const node &n);
  void addEdge(const edge &n);
};

int oppose(int cmpOp);

#endif //RESULTIMPL_HPP
