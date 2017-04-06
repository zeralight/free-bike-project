#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <array>

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
}


Attribute::~Attribute() {}


std::string Attribute::getLabel() const {
  return this->label;
}


int Attribute::getConstraints() const{
  return this->constraints;
}


std::string Attribute::getTypeName() const {
  return this->typeName;
}


void Attribute::setLabel(const std::string &newLabel) {
  this->label = newLabel;
}


void Attribute::setConstraints(int newConstraints) {
  this->constraints = newConstraints;
}


void Attribute::setTypeName(const std::string &newTypeName) {
  this->typeName = newTypeName;
}


void Attribute::addConstraints(int newConstraints) {
  this->constraints |= newConstraints;
}


template <>
INT unserialize<INT>(const std::string &serializedValue, const std::string &format) {
  return std::stoi(serializedValue);
}


template <>
DOUBLE unserialize<DOUBLE>(const std::string &serializedValue, const std::string &format) {
  return std::stod(serializedValue);
}


template <>
BOOL unserialize<BOOL>(const std::string &serializedValue, const std::string &format) {
  if (serializedValue == "true" ||
      serializedValue == "True" ||
      serializedValue == "TRUE" ||
      stoi(serializedValue) != 0)
    return true;
  else
    return false;
}


template <>
STRING unserialize<STRING>(const std::string &serializedValue, const std::string &format) {
  return serializedValue;
}


template <>
std::string serialize(const INT &value) {
  return std::to_string(value);
}


template <>
std::string serialize(const DOUBLE &value) {

}


template <>
std::string serialize(const STRING &value) {

}


template <>
std::string serialize(const BOOL &value) {

}


Attribute * newAttr(const std::string &label, const std::string &typeName) {
  if (typeName == "int")
    return new Attr<INT>(label);
  else if (typeName == "double")
    return new Attr<DOUBLE>(label);
  else if (typeName == "bool")
    return new Attr<BOOL>(label);
  else if (typeName == "string")
    return new Attr<STRING>(label);
  else
    return NULL;
}


void delAttr(Attribute * attr[], int nAttr) {
  for (int i = 0 ; i < nAttr ; i++)
    delete attr[i];
}


/*
template <>
DATE unserialize<DATE>(const std::string &serializedValue, const std::string &format) {
  struct tm t;
  DATE ret;
  memset(&t, 0, sizeof(struct tm));

  strptime(serializedValue.c_str, format.c_str, &t);
  
}
*/
