#ifndef RESULT_HPP
#define RESULT_HPP

#include <string>

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
};

void delResult(Result * res);

#endif //RESULT_HPP

