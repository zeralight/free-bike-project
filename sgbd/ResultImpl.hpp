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
public:
  ResultImpl(Graph *, DatabaseImpl *);
  ~ResultImpl();

  /*
   * Fonction to edit the result's graph nodes matching entity
   */
  bool editResultNodes(Entity&, Attribute **, int);
  
  /*
   * Fonction to edit the result's graph nodes matching relation
   */
  bool editResultEdges(Relation&, Attribute **, int);

  // opérations sur le edge vraiment utile ?
  //temporaire doit bouger dans la hiérarchie d'héritage
  Iterator<node> * getNodes() const;
  Iterator<edge> * getEdges() const;

  // Plus haut dans la hiérarchie ?
  void addNode(const node &n);
  void addEdge(const edge &n);

};

#endif //RESULTIMPL_HPP
