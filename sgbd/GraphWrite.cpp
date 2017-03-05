#include <iostream>
#include <string>
#include <cstdlib>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

#include "GraphWrite.hpp"


GraphWriteAbstract::GraphWriteAbstract(Graph * g, DatabaseImpl * db) {
  this->g = g;
  this->db = db;
}


GraphWriteAbstract::~GraphWriteAbstract() {
  if (g) {
    Graph * supG = g->getSuperGraph();
    if (supG != g)
      supG->delAllSubGraphs(g);
    else
      delete g;
  }
}
