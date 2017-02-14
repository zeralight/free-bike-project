#include <iostream>
#include <cstring>

#include "DBTools.hpp"

template <>
Attr<DOUBLE>::Attr() {
  this->typeName = "double";
}

template <>
Attr<BOOL>::Attr() {
  this->typeName = "bool";
}

template <>
Attr<INT>::Attr() {
  this->typeName = "int";
}

template <>
Attr<STRING>::Attr() {
  this->typeName = "string";
}
