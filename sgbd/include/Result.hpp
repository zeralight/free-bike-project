#ifndef RESULT_HPP
#define RESULT_HPP

#include <iostream>
#include <string>

#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/StringProperty.h>
#include <tulip/DoubleProperty.h>
#include <tulip/IntegerProperty.h>
#include <tulip/BooleanProperty.h>

#include "DBTools.hpp"

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

  virtual void where(std::string label, Attribute * attr[], int nAttr, int cmpOp) =0;

  virtual std::vector<Attribute*> get(std::string labelPattern, std::string attributeName);
};

void delResult(Result * res);

#endif //RESULT_HPP

