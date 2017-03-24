#include <string>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/StringProperty.h>

#include "Pattern.hpp"
#include "DatabaseImpl.hpp"


// pas sensé etre visible ?
#define PROP_TYPE_NAME "ptType"
#define PROP_LABEL_NAME "ptLabel"
#define PROP_CHECKED_NAME "ptChecked"


Pattern::Pattern(DatabaseImpl * db) {
  this->db = db;
  this->g = newGraph();
  this->labelProp = this->g->addLocalProperty<StringProperty>(PROP_TYPE_NAME);
  this->typeProp = this->g->addLocalProperty<StringProperty>(PROP_LABEL_NAME);
  this->checkedProp = this->g->addLocalProperty<BooleanProperty>(PROP_CHECKED_NAME);
}


Pattern::~Pattern() {
  delete this->g;
}


void Pattern::addNode(const std::string &label, const std::string &entityName) {
  node n;
  n = this->g->addNode();
  this->labelProp->setNodeValue(n, label);
  this->typeProp->setNodeValue(n, entityName);
  this->checkedProp->setNodeValue(n, false);
}


void Pattern::addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst) {
  
}
