#ifndef PATTERNIMPL_HPP
#define PATTERNIMPL_HPP

///@cond USER

#include <string>

#include "Database.hpp"
/**
 * @brief This class describes a model which will be search in a graph.
 * This model is a Graph contained in the Pattern. All elements of the Pattern have a unique label.
 **/
class Pattern {
public:
  /**
   * @brief Function to add a node in the Pattern
   *
   * @param label label of the node to add (unique)
   * @param  entityName name of the entity type the node will be
   **/
  virtual void addNode(const std::string &label, const std::string &entityName) =0;

  /**
   * @brief Function to add an edge in the Pattern
   *
   * @param label label of the edge to add (unique) 
   * @param relationName name of the relation type the edge will be
   * @param labelSrc label of the source node
   * @param labelDst label of the destination node
   **/
  virtual void addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst) =0;
};

Pattern * newPattern(Database * db);
void delPattern(Pattern * p);

///@endcond

#endif //PATTERNIMPL_HPP
