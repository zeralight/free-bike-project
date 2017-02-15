#include <iostream>
#include <cstring>

#include "DBTools.hpp"

template <>
void Attr<INT>::init() {
  this->typeName = "int";
};

template <>
void Attr<DOUBLE>::init() {
  this->typeName = "double";
};

template <>
void Attr<BOOL>::init() {
  this->typeName = "bool";
};

template <>
void Attr<STRING>::init() {
  this->typeName = "string";
};
