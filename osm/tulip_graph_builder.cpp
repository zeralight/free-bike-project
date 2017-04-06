#include <QtCore>
#include <QProcess>
#include <QString>
#include <QTextStream>

#include <vector>
#include <iostream>
#include <clocale>
#include <stdexcept>
#include <memory>
#include <string>
#include <map>
#include <random>

#include <tulip/Graph.h>
#include <tulip/TlpTools.h>
#include <tulip/DoubleProperty.h>
#include <tulip/BooleanProperty.h>
#include <tulip/StringProperty.h>
#include <tulip/LayoutProperty.h>
#include <tulip/SizeProperty.h>
#include <tulip/ColorProperty.h>
#include <tulip/IntegerProperty.h>
#include <tulip/ColorScale.h>


#include "OsmParser.hpp"
#include "ShortestPaths.hpp"
#include "misc.hpp"


struct Edge {
    size_t src;
    size_t dest;
    friend bool operator<(Edge const& lhs, Edge const& rhs) {
        return (lhs.src < rhs.src) || (lhs.src == rhs.src && lhs.dest < rhs.dest);
    }
};

void usage();
void run(char* const);
std::tuple<osm::Nodes, std::vector<Edge>, std::map<Edge, std::vector<size_t>>> processInput(QTextStream&);

int main(int argc, char **argv)
{
    if (argc < 2) {
        usage();
        return 0;
    }
    QCoreApplication app(argc, argv);
    tlp::initTulipLib();
    run(argv[1]);
    return 0;
}

void usage() {
    std::cout << "Usage: ./parser osm-xml-map_path\n";
}

void run(char* const filePath) {
    try {
        // launch calculations_paths process (which will invoke osm graph downloading and parsing)
        QProcess calculationsPathsProcess(nullptr);
        calculationsPathsProcess.start("./paths_calculations", QStringList(filePath));
        calculationsPathsProcess.waitForFinished(-1);

        // read output
        auto outputProcess = std::make_unique<QString>(calculationsPathsProcess.readAllStandardOutput());
        auto inputStream = std::make_unique<QTextStream>(outputProcess.get());
        //auto graphAndPaths = osm::buildGraphAndPaths(*inputStream);
        auto graphAndPaths = processInput(*inputStream);
        auto const& nodes = std::get<0>(graphAndPaths);
        //auto const& adjacencyList = std::get<1>(graphAndPaths);
        auto const& edges = std::get<1>(graphAndPaths);
        auto const& paths = std::get<2>(graphAndPaths);
        outputProcess.reset(nullptr);
        inputStream.reset(nullptr);
        /*
            build the graph
        */
        auto tulipGraph = std::unique_ptr<tlp::Graph>(tlp::newGraph());
        
        // nodes
        std::vector<tlp::node> tulipNodes(nodes.size());
        for (size_t i = 0; i < nodes.size(); ++i) {
            tulipNodes[i] = tulipGraph->addNode();
        }
        // edges
        
        // adding normal edges
        std::vector<tlp::edge> tulipEdges;
        tulipEdges.reserve(edges.size());
        for (auto const& e: edges) {
            tulipEdges.push_back(tulipGraph->addEdge(tulipNodes[e.src], tulipNodes[e.dest]));
        }
        
        std::map<Edge, size_t> edgesMapper;
        std::map<Edge, tlp::edge> tulipPaths;
        for (size_t i = 0; i < edges.size(); ++i) {
            edgesMapper[edges[i]] = i;
        }
        /*
            properties
        */

        // latitude, longitude and isBicycleParking properties
        auto latitudeProperty = tulipGraph->getLocalProperty<tlp::DoubleProperty>("latitude");
        auto longitudeProperty = tulipGraph->getLocalProperty<tlp::DoubleProperty>("longitude");
        auto isBicycleProperty = tulipGraph->getLocalProperty<tlp::BooleanProperty>("isBicycleParking");
        latitudeProperty->setAllNodeValue(0.);
        latitudeProperty->setAllEdgeValue(0.);
        longitudeProperty->setAllNodeValue(0.);
        longitudeProperty->setAllEdgeValue(0.);
        isBicycleProperty->setAllNodeValue(false);
        isBicycleProperty->setAllEdgeValue(false);
        for (size_t i = 0; i < nodes.size(); ++i) {
            latitudeProperty->setNodeValue(tulipNodes[i], nodes[i].latitude);
            longitudeProperty->setNodeValue(tulipNodes[i], nodes[i].longitude);
            isBicycleProperty->setNodeValue(tulipNodes[i], nodes[i].isBicycleParking);
        }

        // nextHop property
        // stored as a string because IntProperty can't hold all possible ids: the real type of nodes
        // changed of mind: current cities have nodes(required for this implementation) < 10^9
        auto nextHopProperty = tulipGraph->getLocalProperty<tlp::IntegerVectorProperty>("nextHop");
        nextHopProperty->setAllNodeValue(std::vector<int>());
        nextHopProperty->setAllEdgeValue(std::vector<int>());

        for (auto const& kv: paths) {
            auto const& edge = kv.first;
            auto const& destinations = kv.second;
            std::vector<std::string> strDestinations(destinations.size());
            for (size_t i = 0; i < destinations.size(); ++i) {
                strDestinations[i] = std::to_string(tulipNodes[destinations[i]]);
            }
            std::vector<int> v(destinations.size());
            for (size_t i = 0; i < v.size(); ++i) v[i] = destinations[i];
            nextHopProperty->setEdgeValue(tulipEdges[edgesMapper[edge]], v);
        }
        
        // viewLayout property
        auto viewLayoutProperty = tulipGraph->getLocalProperty<tlp::LayoutProperty>("viewLayout");
        viewLayoutProperty->setAllNodeValue(tlp::Coord());
        viewLayoutProperty->setAllEdgeValue(std::vector<tlp::Coord>());
        for (size_t i = 0; i < nodes.size(); ++i) {
            auto xy = osm::gpsToCartesian(nodes[i].latitude, nodes[i].longitude);
            viewLayoutProperty->setNodeValue(tulipNodes[i], tlp::Coord(xy.first, xy.second, 0.));
        }

        // viewSize property
        // show only bicycle nodes and highway edges
        auto viewSizeProperty = tulipGraph->getLocalProperty<tlp::SizeProperty>("viewSize");
        viewSizeProperty->setAllNodeValue(tlp::Size(0, 0, 0));
        viewSizeProperty->setAllEdgeValue(tlp::Size(0.0001, 0.0001, 0.0001));
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (nodes[i].isBicycleParking)
                viewSizeProperty->setNodeValue(tulipNodes[i], tlp::Size(0.0005, 0.0005, 0.0005));
        }
        for (size_t i = 0; i < tulipEdges.size(); ++i) {
            viewSizeProperty->setEdgeValue(tulipEdges[i], tlp::Size(0.0001, 0.0001, 0.0001));
        }

        // save the graph
        tlp::saveGraph(tulipGraph.get(), std::string(filePath)+".tlp");
    } catch (std::logic_error const& e) {
        std::cerr << e.what() << '\n';
    }
}

std::tuple<osm::Nodes, std::vector<Edge>, std::map<Edge, std::vector<size_t>>>
processInput(QTextStream& in) {
    // nodes
    osm::Nodes nodes;
    size_t nbNodes;
    in >> nbNodes;
    nodes.resize(nbNodes);
    for (auto& n: nodes) {
        int b;
        in >> n.id >> n.longitude >> n.latitude >> b;
        n.isBicycleParking = b;
    }


    // edges
    std::vector<Edge> edges;
    for (size_t i = 0; i < nbNodes; ++i) {
        size_t nb;
        in >> nb;
        edges.reserve(edges.size()+nb);
        for (size_t j = 0; j < nb; ++j) {
            size_t x;
            double d; // distance is currently ignored because not used
            in >> x >> d;
            edges.push_back({i, x});
        }
    }
    
    // paths: paths[{src, dest}] = X <=> nexthop from src to every node in X is dest
    std::map<Edge, std::vector<size_t>> paths;
    size_t nbPaths;
    in >> nbPaths;
    for (size_t i = 0; i < nbPaths; ++i) {
        size_t src, dest, elemsSize;
        double dist;
        in >> src >> dest >> dist >> elemsSize; // dist is currently ignored because not used
        in >> src; // skip the 1st element (which is src)
        for (size_t j = 1; j < elemsSize; ++j) {
            size_t nextHop;
            in >> nextHop;
            paths[{src, nextHop}].push_back(dest);
            src = nextHop;
        }
    }
    // remove redundant values
    for (auto &kv: paths) {
        auto& v = kv.second;;
        std::sort(std::begin(v), std::end(v));
        v.erase( std::unique(std::begin(v), std::end(v)), std::end(v) );
    }
    return std::make_tuple(nodes, edges, paths);

}

static std::vector<std::tuple<size_t, size_t, double>>
linearizeAdjacencyList(osm::AdjacencyList const& adjacencyList) {
        std::vector<std::tuple<size_t, size_t, double>> edges;
        size_t edgesSize = 0;
        for (auto const& e: adjacencyList)
            edgesSize += e.size();
        edges.reserve(edgesSize);
        for (size_t i = 0; i < adjacencyList.size(); ++i) {
            for (auto const& e: adjacencyList[i])
                edges.push_back(std::make_tuple(i, e.first, e.second));
        }

        return edges;
}

static std::vector<std::tuple<size_t, size_t, size_t>>
linearizePaths(osm::Paths const& paths) {
    std::vector<std::tuple<size_t, size_t, size_t>> edges;
    for (auto const& p: paths) {
        auto dest = p.dest;
        for (size_t i = 0; i+1 < p.elems.size(); ++i) {
            auto curr = p.elems[i];
            auto nextHop = p.elems[i+1];
            edges.push_back(std::make_tuple(curr, dest, nextHop));
        }
    }

    return edges;
}
