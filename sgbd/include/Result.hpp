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

class Result {
public:
  /*
   * Fonction to edit the result's graph nodes matching entity
   */
  virtual bool editNodes(const std::string &entityName, Attribute * attr[], int nAttr) =0;
  
  /*
   * Fonction to edit the result's graph nodes matching relation
   */
  virtual bool editEdges(const std::string &relationName, Attribute * attr[], int nAttr) =0;

  /**
   * @copydoc Database::match(Pattern *)
   **/
  virtual Result * match(Pattern * p) =0;
  
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
