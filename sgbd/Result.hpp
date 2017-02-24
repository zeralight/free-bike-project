#ifndef RESULT_HPP
#define RESULT_HPP

#include "Database.hpp"
#include "Entity.hpp"
#include "Relation.hpp"

class Result{
private:
  Graph * G;//this graph is a particular graph, subgraph of a global graph
  Database * db;

public:
  Result(Graph *, Database *);

  /*
Fonction to remove the result's graph from the global graph and the database
  */
  void removeResult();

  /*
Fonction to edit the result's graph nodes matching entity
  */
  bool editResultNodes(Entity&, Attribute **, int);
  
    /*
Fonction to edit the result's graph nodes matching relation
  */
  bool editResultEdges(Relation&, Attribute **, int);

};




#endif
