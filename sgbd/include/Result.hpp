#ifndef RESULT_HPP
#define RESULT_HPP

///@cond USER

#include <iostream>
#include <string>

#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/StringProperty.h>
#include <tulip/DoubleProperty.h>
#include <tulip/IntegerProperty.h>
#include <tulip/BooleanProperty.h>

#include "DBTools.hpp"
#include "Pattern.hpp"

/**
 * @brief This class allows to store queries answers and can be use as a Database object(almost).
 *
 **/
class Result {
public:
  /**
   * @brief Edition of nodes in the Database
   *
   * This method edits the instances of the entity specified by 'entityName'. The new values with which they are modified are put in the Attribute elements of the array 'attr'. 
   * Only existing attributes for 'entityName' are accepted, if only one argument is incorrect, the method fails.
   *
   * @param entityName name of the edited nodes' entity 
   * @param attr list of the attributes to modify and their new value
   * @param nAttr size of attr
   *
   * @return bool : whether the edition was successful or not
   *
   * @sa Attribute to know how to put a desired value in an Attribute object
   **/
  virtual bool editNodes(const std::string &entityName, Attribute * attr[], int nAttr) =0;
  
  /**
   * @brief Edition of edges in the Database
   *
   *
   * This method edits the instances of the relation specified by 'relationName'. The new values with which they are modified are put in the Attribute elements of the array 'attr'. 
   * Only existing attributes for 'relationName' are accepted, if only one argument is incorrect, the method fails.
   *
   * @param entityName name of the edited nodes' entity 
   * @param attr list of the attributes to modify and their new value
   * @param nAttr size of attr
   *
   * @return bool : whether the edition was successful or not
   *
   * @sa Attribute to know how to put a desired value in an Attribute object
   **/
  virtual bool editEdges(const std::string &relationName, Attribute * attr[], int nAttr) =0;
  
  /**
   * @brief Matching of pattern in the database 
   *
   * Finds in the database the elements which match the pattern passed in argument. All occurencies found are added to the returned result.
   * 
   * @param p the pattern which has to be matched in the database
   * 
   * @return Result * : pointer to the %Result object which contains the the data matched.
   *
   * @warning In case a Pattern is formed by a forest of graphes, the behaviour of this function is unknown (but probably false). The graph of the pattern must be in one chunk, and may not contain isolated nodes.
   * 
   * @sa Pattern to know how to create a pattern
   **/
  virtual Result * match(Pattern * p) =0;

   /**
   * @brief Filtering of the Result's graph
   *
   * The graph of the Result is filtered : only the nodes or edges with the wanted attributes are kept if the comparaison operator choose is EQUAL, the opposite if the operator is DIFFERENT.
   *
   * @param label label of a node or an edge in the graph
   * @param attr list of attribute used in order to filter
   * @param nAttr size of attr
   * @param cmpOp int corresponding to the filtering choice : EQUAL or DIFFERENT
   **/
  virtual void where(std::string label, Attribute * attr[], int nAttr, int cmpOp) =0;

  virtual std::vector<Attribute *> * get(const std::string &label, const std::string &attributeName) const =0;
};


/**
 * @brief Deletion of a Result object
 *
 * All associated resources are freeed, so the pointer res is invalidated.
 * If res is NULL, nothing will be done.
 *
 * @param res pointer to the Result object to be deleted.
 **/
void delResult(Result * res);

///@endcond

#endif //RESULT_HPP
