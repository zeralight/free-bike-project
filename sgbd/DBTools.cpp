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
