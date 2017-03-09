#include <QtCore>
#include <QProcess>
#include <QString>
#include <QTextStream>

#include <tulip/Graph.h>
#include <tulip/TlpTools.h>
#include <tulip/DoubleProperty.h>
#include <tulip/BooleanProperty.h>
#include <tulip/StringProperty.h>
#include <tulip/LayoutProperty.h>
#include <tulip/SizeProperty.h>

#include <iostream>
#include <clocale>
#include <stdexcept>
#include <memory>
#include <string>
#include <map>

#include "OsmParser.hpp"
#include "ShortestPaths.hpp"
#include "misc.hpp"

/*
    This file is incomplete
*/
void usage();
void run(char* const);
int main(int argc, char **argv)
{
    if (argc < 2) {
        usage();
        return 0;
    }
    QCoreApplication app(argc, argv);
    tlp::initTulipLib();
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // Avoid system floatting number representation (like 25,25)
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
        auto graphAndPaths = osm::buildGraphAndPaths(*inputStream);
        auto const& nodes = std::get<0>(graphAndPaths);
        auto const& adjacencyList = std::get<1>(graphAndPaths);
        auto const& paths = std::get<2>(graphAndPaths);
        outputProcess.reset(nullptr);
        inputStream.reset(nullptr);
        
        /*
            build the graph
        */
        auto tulipGraph = std::unique_ptr<tlp::Graph>(tlp::newGraph());
        
        // nodes
        // tulipNodes[i] is mapped to nodes[i]
        std::vector<tlp::node> tulipNodes(nodes.size());
        for (size_t i = 0; i < nodes.size(); ++i) {
            tulipNodes[i] = tulipGraph->addNode();
            // node i will be represented in tulipGraph by tulipNodes[i]
        }
/*
        // edges
        // linearize adjacencyList
        std::vector<std::tuple<size_t, size_t, double>> edges;
        size_t edgesSize = 0;
        for (auto const& e: adjacencyList)
            edgesSize += e.size();
        edges.reserve(edgesSize);
        // copy adjacencyList to edges
        for (size_t i = 0; i < adjacencyList.size(); ++i) {
            for (auto const& e: adjacencyList[i])
                edges.push_back(std::make_tuple(i, e.first, e.second));
        }
*/
/*
        // adding normal edges
        std::vector<tlp::edge> tulipNormalEdges;
        tulipNormalEdges.reserve(edges.size());
        // add edges
        tulipNormalEdges.reserve(edges.size());
        for (auto const& e: edges)
            tulipNormalEdges.push_back(tulipGraph->addEdge(tulipNodes[std::get<0>(e)], tulipNodes[std::get<1>(e)]));


        // adding shortest paths edges
        std::vector<tlp::edge> tulipPathsEdges(paths.size());
        for (size_t i = 0; i < paths.size(); ++i) {
            // do not store paths where src = dest
            if (paths[i].src != paths[i].dest)
                tulipPathsEdges[i] = tulipGraph->addEdge(tulipNodes[paths[i].src], tulipNodes[paths[i].nextHop]);
        }
*/

        std::map<std::pair<size_t, size_t>, tlp::edge> tulipEdges;
        for (auto const& p: paths) {
            auto a = p.src;
            auto b = p.nextHop;
            if (tulipEdges.find({a, b}) == std::end(tulipEdges)) {
                tulipEdges[{a, b}] = tulipGraph->addEdge(tulipNodes[a], tulipNodes[b]);
            }
            if (tulipEdges.find({b, a}) == std::end(tulipEdges)) {
                tulipEdges[{b, a}] = tulipGraph->addEdge(tulipNodes[b], tulipNodes[a]);
            }
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

        // viewLayout property
        auto viewLayoutProperty = tulipGraph->getLocalProperty<tlp::LayoutProperty>("viewLayout");
        viewLayoutProperty->setAllNodeValue(tlp::Coord());
        viewLayoutProperty->setAllEdgeValue(std::vector<tlp::Coord>());
        for (size_t i = 0; i < nodes.size(); ++i) {
            auto xy = osm::gpsToCartesian(nodes[i].latitude, nodes[i].longitude);
            viewLayoutProperty->setNodeValue(tulipNodes[i], tlp::Coord(xy.first, xy.second, 0.));
        }
/*
        // nextHop property
        // stored as a string because IntProperty can't hold all possible ids: the real type of nodes
        auto nextHopProperty = tulipGraph->getLocalProperty<tlp::StringProperty>("nextHop");
        nextHopProperty->setAllNodeValue("");
        nextHopProperty->setAllEdgeValue("");
        for (size_t i = 0; i < paths.size(); ++i) {
            if (paths[i].src != paths[i].dest) {
                nextHopProperty->setEdgeValue(tulipPathsEdges[i], std::to_string(paths[i].dest));
            }
        }
*/

        // viewSize property
        // this property is explicitly set because tulip is automatically generating inconvenient values
        auto viewSizeProperty = tulipGraph->getLocalProperty<tlp::SizeProperty>("viewSize");
        viewSizeProperty->setAllNodeValue(tlp::Size(0.0001, 0.0001, 0.0001));
        viewSizeProperty->setAllEdgeValue(tlp::Size(0.000125, 0.000125, 0.000125));

        // save the graph
        tlp::saveGraph(tulipGraph.get(), std::string(filePath)+".tlp");
    } catch (std::logic_error const& e) {
        std::cerr << e.what() << '\n';
    }
}


