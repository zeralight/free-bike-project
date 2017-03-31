#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"

using namespace tlp;


// See DBTools.hpp for direction type definition

//Iterator<edge> * getItEdges(const Graph * g, const node * nA, const node * nB, direction dir);

std::vector<node> * getNodes(const Graph * g, Attribute * attr[], int nAttr, int cmpOp);
std::vector<edge> * getEdges(const Graph * g, const node &nA, const node &nB, Attribute * attr[], int nAttr, direction dir, int cmpOp);
std::vector<edge> * getEdges(const Graph * g, const node &n, Attribute * attr[], int nAttr, direction dir, int cmpOp);
std::vector<edge> * getEdges(const Graph * g, Attribute * attr[], int nAttr, int cmpOp);
std::vector<edge> * getEdges(Iterator<edge> * it, Attribute * attr[], int nAttr, int cmpOp);
  
#endif //TOOLS_HPP
