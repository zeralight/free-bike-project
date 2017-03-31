#ifndef RESULTIMPL_HPP
#define RESULTIMPL_HPP

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>

#ifndef DATABASE_HPP
#include "Database.hpp"
#include "Entity.hpp"
#include "Relation.hpp"
#include "DatabaseImpl.hpp"
#endif //DATABASE_HPP

#include "GraphWrite.hpp"
#include "Result.hpp"

class DatabaseImpl;


class ResultImpl : public GraphWriteAbstract, public Result {
  using GraphWriteAbstract::editNodes;
  using GraphWriteAbstract::editEdges;
  
public:
  ResultImpl(const std::string &name, Graph *, DatabaseImpl *);
  ~ResultImpl();
  
  // opérations sur le edge vraiment utile ?
  //temporaire doit bouger dans la hiérarchie d'héritage
  Iterator<node> * getNodes() const;
  Iterator<edge> * getEdges() const;
  
  bool editNodes(const std::string &entityName, Attribute * attr[], int nAttr);  
  bool editEdges(const std::string &relationName, Attribute * attr[], int nAttr);
  void filterNodes(string entityName, Attribute * attr[], int nAttr, int cmpOp);
  void filterEdges(string relationName, Attribute * attr[], int nAttr, int cmpOp);
  void where(string label, Attribute * attr[], int nAttr, int cmpOp);  

  // Plus haut dans la hiérarchie ?
  void addNode(const node &n);
  void addEdge(const edge &n);
};

#endif //RESULTIMPL_HPP
