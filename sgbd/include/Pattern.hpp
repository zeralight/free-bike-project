#ifndef PATTERNIMPL_HPP
#define PATTERNIMPL_HPP

///@cond USER

#include <string>

#include "Database.hpp"

class Pattern {
public:  
  virtual void addNode(const std::string &label, const std::string &entityName) =0;
  virtual void addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst) =0;
};

Pattern * newPattern(Database * db);
void delPattern(Pattern * p);

///@endcond

#endif //PATTERNIMPL_HPP
