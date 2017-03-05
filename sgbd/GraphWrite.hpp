#ifndef GRAPHWRITE_HPP
#define GRAPHWRITE_HPP

#include <string>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

using namespace tlp;

class DatabaseImpl;

class GraphWrite {
};

class GraphWriteAbstract: public GraphWrite {
protected:
  Graph * g;
  DatabaseImpl * db;

protected:
  GraphWriteAbstract(Graph * g, DatabaseImpl * db);
  ~GraphWriteAbstract();
};


#endif //GRAPHWRITE_HPP
