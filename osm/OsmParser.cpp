#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <cassert>
#include <iostream>
#include <memory>

#include <QXmlStreamReader>

#include "OsmParser.hpp"
#include "InternalNode.hpp"
#include "Node.hpp"
#include "misc.hpp"

namespace osm {

QString const tagOsm = "osm";
QString const tagNode = "node";
QString const tagWay = "way";
QString const tagNd = "nd";
QString const tagTag = "tag";

QString const attrNodeId = "id";
QString const attrNdRef = "ref";
QString const attrNodeLon = "lon";
QString const attrNodeLat = "lat";
QString const attrTagKey = "k";
QString const attrTagVal = "v";

QString const valAmenity = "amenity";
QString const valBicycleParking = "bicycle_parking";


OsmParser::OsmParser(QFile &file) : reader(&file), _ready(true) {}

std::pair<Nodes, AdjacencyList> OsmParser::parse() {
	if (!_ready)
		throw std::logic_error("Parser not ready");

    // allocating explictly containers on heap to release them as soon as possible
    auto pNodes = std::make_unique<std::unordered_map<NodeIndexType, OsmNode>>(); 
    auto pWays = std::make_unique<std::vector<std::vector<NodeIndexType>>>(); 
    auto pOrderedNodes = std::make_unique<std::vector<NodeIndexType>>(); 
    auto pNodesPosInOrderedNodes = std::make_unique<std::unordered_map<NodeIndexType, size_t>>(); 

    auto& nodes = *pNodes;
    auto& ways = *pWays;
    auto& orderedNodes = *pOrderedNodes;
    auto& nodesPosInOrderedNodes = *pNodesPosInOrderedNodes;

    /*
	std::unordered_map<NodeIndexType, OsmNode> nodes;
    std::vector<std::vector<NodeIndexType>> ways;
    std::vector<NodeIndexType> orderedNodes;
    std::unordered_map<NodeIndexType, size_t> nodesPosInOrderedNodes;
    */
#ifdef DEBUG_VELO
#warning "DEBUG_VELO is set"
#endif

	std::stack<State> state;
	NodeIndexType ndId;
	Node node;
	std::vector<NodeIndexType> way;
	while (!reader.hasError() && !reader.atEnd()) {
		reader.readNext();
		//std::cerr << reader.name().toString() << std::endl;
		if (reader.isStartElement()) {
			auto const &name = reader.name().toString();
			//std::cerr << "<" << reader.name().toString() << ">" << std::endl;
			
			if (name == tagNode && !state.empty() && state.top() == State::osm) { // <osm><node>
				state.push(State::node);
			}
			else if (name == tagWay && !state.empty() && state.top() == State::osm) { // <osm><way>
				state.push(State::way);
			}
			else if (name == tagNd && !state.empty() && state.top() == State::way) { // <osm><way><nd>
				state.push(State::nd);
			}
			else if (name == tagOsm && state.empty()) {
				state.push(State::osm);
			}
			else if (name == tagTag && !state.empty() && state.top() == State::node) { // <osm><node><tag>
				state.push(State::tag);
			}
			else { // Ignore everything else
				reader.readElementText(QXmlStreamReader::SkipChildElements);
				continue;
			}

			auto const &attrs = reader.attributes();
			for (auto const &e: attrs) {
				//std::cerr << e.name().toString() << '=' << e.value().toString() << std::endl;
				auto const &eName = e.name().toString();
				auto const &eValue = e.value().toString();
				if (eName == attrNodeId && state.top() == State::node) { // <node id=..>
				   node.setId(std::stoul(eValue.toStdString())); 
				}
				else if (eName == attrNodeLat && state.top() == State::node) { // <node lat=..>
                    node.setLatitude(std::stod(eValue.toStdString()));
				}
				else if (eName == attrNodeLon && state.top() == State::node) { // <node lon=..>
					node.setLongitude(std::stod(eValue.toStdString()));
				}
				else if (eName == attrNdRef && state.top() == State::nd) { // <way><nd ref="..">
					ndId = std::stoul(eValue.toStdString());
				}
				else if (eName == attrTagKey && eValue == valAmenity
						&& state.top() == State::tag) { // <tag k="amenity">
					node.setAmenityKey();
				}
				else if (eName == attrTagVal && eValue == valBicycleParking
						&& state.top() == State::tag) { // <tag v="bicycle_parking">
					node.setBicycleParkingValue();
				}
			}
		}
		else if (reader.isEndElement()) {
			auto const &name = reader.name().toString();
			//std::cerr << "</" << reader.name().toString() << ">" << std::endl;

			if (name == tagNode && !state.empty() && state.top() == State::node) { // </node> 
				//std::cerr << node.hasId() << ' ' << node.hasLongitude() << ' ' << node.hasLatitude() << '\n';
				if (node.validState()) {
					nodes.insert({node.id(), OsmNode(node)});
					orderedNodes.push_back(node.id());
                    nodesPosInOrderedNodes[node.id()] = orderedNodes.size()-1;
				} // else: missing required information about the node
				state.pop();
				node.reset();
			}
			else if (name == tagWay && !state.empty() && state.top() == State::way) { // </way> 
				ways.push_back(way);
				way.clear();
				state.pop();
			}
			else if (name == tagNd && !state.empty() && state.top() == State::nd) { // </nd>
				way.push_back(ndId);
				state.pop();
			}
			else if (name == tagOsm && !state.empty() && state.top() == State::osm) {
				state.pop();
			}
			else if (name == tagTag && !state.empty() && state.top() == State::tag) {
				state.pop();
			}
			else if (name != tagOsm && name != tagNd && name != tagNode) {
				continue;
			}
			// else: error reported automatically by reader.hasError()
		}
	}

	if (reader.hasError())
		throw std::logic_error(("XML file isn't well-formed:" + reader.errorString()).toStdString());

	_ready = false;

    /*
        remove every node in route not figuring in nodes
    */
#ifdef DEBUG_VELO
    size_t removedEdges = 0;
#endif
    for (auto& w: ways) {
        std::vector<NodeIndexType> cleanWay;
        for (auto it = std::begin(w); it != std::end(w); ++it) {
            if (nodes.find(*it) != std::end(nodes)) {
                cleanWay.push_back(*it);
            }
#ifdef DEBUG_VELO
            else {
                ++removedEdges;
            }
#endif
        }
        w = std::move(cleanWay);
    }

    /*
        remove non bicycleStations having 0 edge
    */
    auto pConnectedNodes = std::make_unique<std::unordered_set<NodeIndexType>>();
    auto& connectedNodes = *pConnectedNodes;
    for (auto const& w: ways) {
        for (auto const& n: w) {
            connectedNodes.insert(n);
        }
    }
    //  list all bicycle stations
    std::unordered_set<NodeIndexType> bicycleNodes;
    for (auto const& n: nodes) {
        if (n.second.isBicycleParking)
            bicycleNodes.insert(n.first);
    }
    auto pRemovedNodes = std::make_unique<std::vector<NodeIndexType>>();
    auto& removedNodes = *pRemovedNodes;
    for (auto const& n: nodes) {
        if (connectedNodes.find(n.first) == std::end(connectedNodes)) {
            if (bicycleNodes.find(n.first) == std::end(bicycleNodes)) { // add it to the removedNodes
                removedNodes.push_back(n.first);
            }
        }
    }
    for (auto const& n: removedNodes) {
        nodes.erase(nodes.find(n));
    }
    pRemovedNodes.reset(nullptr);

    /*
        connect every bicycleStation having 0 edge to the closest connected nodes
    */
    for (auto const& n: nodes) {
        // connecting non-connected bicycle-nodes to the L closest connected nodes
        auto constexpr L = 5;
        if (connectedNodes.find(n.first) == std::end(connectedNodes) && bicycleNodes.find(n.first) != std::end(bicycleNodes)) {
            auto const& n1 = nodes[n.first];
            size_t i = nodesPosInOrderedNodes[n.first];
            size_t j = i+1;
            bool hasLeft = i--;
            int k;
            for (k = 0; k < L && hasLeft && j < orderedNodes.size();) {
                if (connectedNodes.find(orderedNodes[i]) == std::end(connectedNodes)) {
                    hasLeft = i--;
                    continue;
                }
                if (connectedNodes.find(orderedNodes[j]) == std::end(connectedNodes)) {
                    ++j;
                    continue;
                }
                auto const& n2 = nodes[orderedNodes[i]];
                auto const& n3 = nodes[orderedNodes[j]];
                auto d1 = haversineDist(n1.latitude, n1.longitude, n2.latitude, n2.longitude);
                auto d2 = haversineDist(n1.latitude, n1.longitude, n3.latitude, n3.longitude);
                if (d1 < d2) {
                    ways.push_back({n.first, orderedNodes[i]});
                    hasLeft = i--; 
                }
                else {
                    ways.push_back({n.first, orderedNodes[j]});
                    ++j;
                }
                ++k;
            }
            for (; k < L && hasLeft;) {
                if (connectedNodes.find(orderedNodes[i]) == std::end(connectedNodes)) {
                    hasLeft = i--;
                    continue;
                }
                ways.push_back({n.first, orderedNodes[i]});
                hasLeft = i--;
                ++k;
            }
            for (; k < L && j < orderedNodes.size(); ++k) {
                if (connectedNodes.find(orderedNodes[j]) == std::end(connectedNodes)) {
                    ++j;
                    continue;
                }
                ways.push_back({n.first, orderedNodes[j]});
                ++j;
                ++k;
            }
        }
    }
    // release memory not needed anymore
    pOrderedNodes.reset(nullptr);
    pNodesPosInOrderedNodes.reset(nullptr);
    pConnectedNodes.reset(nullptr);
    
    /*
        Building the graph
    */
    Nodes finalNodes;
    AdjacencyList edges;
    std::unordered_map<NodeIndexType, size_t> mapper;

    finalNodes.reserve(nodes.size());
    edges.reserve(nodes.size());
    mapper.reserve(nodes.size());

    // final nodes
    for (auto const& node: nodes) {
        mapper[node.first] = finalNodes.size();
        finalNodes.push_back(node.second);
    }
    pNodes.reset(nullptr);

    // calculate adjacency list size
    auto pNodesEdgesCounter = std::make_unique<std::vector<size_t>>(finalNodes.size());
    auto& nodesEdgesCounter = *pNodesEdgesCounter;
    for (auto const& w: ways) {
        for (size_t i = 0; i+1 < w.size(); ++i)
            ++nodesEdgesCounter[mapper[w[i]]];
        if (w.size() > 1)
            ++nodesEdgesCounter[mapper[w.back()]];
    }
    // build adjacency list
    edges.resize(finalNodes.size());
    for (size_t i = 0; i < edges.size(); ++i)
        edges[i].reserve(nodesEdgesCounter[i]);
    for (auto const& w: ways) {
        for (size_t i = 0; i+1 < w.size(); ++i) {
            auto const& node1 = finalNodes[mapper[w[i]]];
            auto const& node2 = finalNodes[mapper[w[i+1]]];
            //auto const& node1 = nodes[w[i]];
            //auto const& node2 = nodes[w[i+1]];
            double dist = haversineDist(node1.latitude, node1.longitude, node2.latitude, node2.longitude);
            edges[mapper[node1.id]].push_back({mapper[node2.id], dist});
            edges[mapper[node2.id]].push_back({mapper[node1.id], dist});
        }
    }

    /*
        End
    */
#ifdef DEBUG_VELO
    std::cerr.precision(15);
    std::cerr << "\n\n\n --------- AdjacencyList Display -------------- \n";
    std::cerr << "MAPPING:\n";
    for (auto const& n: mapper) {
        std::cerr << n.first << " => " << n.second << '\n';
        assert (finalNodes[n.second].id == n.first);
    }

	size_t nbBicycleParkings = 0;
    std::cerr.precision(15);
	std::cerr << "\n-----------------------------------------------------------\n";
	std::cerr << "Nodes:\n";
	for (auto const& node: finalNodes) {
		std::cerr << node.id << ' ' << node.latitude << ' ' 
			<< node.longitude << ' ' << node.isBicycleParking << '\n';
		if (node.isBicycleParking)
			++nbBicycleParkings;
	}
	std::cerr << "\n\n--------------------------------------\nEdges:\n";
	for (size_t i = 0; i < edges.size(); ++i) {
        for (auto const& e: edges[i]) {
            std::cerr << "Edge from " << finalNodes[i].id << " to " << finalNodes[e.first].id << " with dist = " << e.second << '\n';
        }
    }
	
    std::cerr << "Total nodes " << finalNodes.size()
        << "\nTotal bicycle nodes " << nbBicycleParkings 
        << "\nTotal edges " << edges.size() 
        << "\nTotal removed edges " << removedEdges << '\n';

#endif
/*
    OsmGraph res;

    for (auto const &node: nodes) {
        res[node.first].first = node.second;
    }
    for (auto const &w: ways) {
        for (size_t i = 0; i+1 < w.size(); ++i) {
            assert (nodes.find(w[i]) != std::end(nodes));
            auto const& node1 = nodes[w[i]];
            auto const& node2 = nodes[w[i+1]];

            double dist = haversineDist(node1.latitude, node1.longitude, node2.latitude, node2.longitude);
            res[node1.id].first = node1;
            res[node2.id].first = node2;
            res[node1.id].second[node2.id] = dist;
            res[node2.id].second[node1.id] = dist;
            auto q1 = mapper[node1.id];
            auto q2 = mapper[node2.id];
            auto itt = std::begin(edges[q1]);
            for (; itt != std::end(edges[q1]) && itt->first != q2; ++itt);
            assert (itt != std::end(edges[q1]));
#ifdef DEBUG_VELO
            std::cerr << node1.latitude << ' ' << node1.longitude << ", " << node2.latitude << ' ' << node2.longitude
                << " " << dist << ' ' << itt->second << std::endl;
#endif
            assert (itt->second == itt->second);
            assert (std::abs(itt->second-dist) < 1e-4);
            
            itt = std::begin(edges[q2]);
            for (; itt != std::end(edges[q2]) && itt->first != q1; ++itt);
            assert (itt != std::end(edges[q2]));
            assert (itt->first == q1);
#ifdef DEBUG_VELO
            std::cerr << itt->second << std::endl;
#endif
            assert (std::abs(itt->second - dist) < 1e-4);
        }
    }
#ifdef DEBUG_VELO
	nbBicycleParkings = 0;
	std::cerr << "\n-----------------------------------------------------------\n";
	std::cerr << "Nodes:\n";
	for (auto const& node: nodes) {
		std::cerr << node.first << ' ' << node.second.latitude << ' ' 
			<< node.second.longitude << ' ' << node.second.isBicycleParking << '\n';
		if (node.second.isBicycleParking)
			++nbBicycleParkings;
	}
	std::cerr << "\n\n--------------------------------------\nWays:\n";
	for (auto const &way: ways) {
		std::cerr << "-------------------------------------------------\n";
		for (auto const &nd: way)
			std::cerr << nd << ' ';
		std::cerr << '\n';
	}
	std::cerr << "--------------------------------\n\n";
	std::cerr << "\n\n";
    std::cerr << "Distances:\n";
    size_t edgesCount = 0;
    for (auto const& it: res) {
        auto const& node = it.first;
        for (auto const& neighbor: it.second.second) {
            std::cerr << "Distance between " << node << " and " << neighbor.first << " = " << neighbor.second << '\n';
            ++edgesCount;
        }
    }
	std::cerr << "Total nodes " << nodes.size()
        << "\nTotal bicycle nodes " << nbBicycleParkings 
        << "\nTotal ways " << ways.size()
        << "\nTotal edges " << edgesCount
        << "\nTotal removed edges " << removedEdges << std::endl;
#endif
*/

    return {std::move(finalNodes), std::move(edges)};
}

// utility functions to pipe results
void printGraph(Nodes const& nodes, AdjacencyList const& edges) {
    using std::cout;

    cout << nodes.size() << '\n';
    for (auto const& node: nodes) {
        cout << node.id << ' ' << node.longitude << ' ' << node.latitude << ' ' << node.isBicycleParking << '\n';
    }

    for (auto const& e: edges) {
        cout << e.size() << '\n';
        for (auto const& neighbor: e) {
            cout << neighbor.first << ' ' << neighbor.second << '\n';
        }
    }
}

std::pair<osm::Nodes, osm::AdjacencyList> buildGraph(QTextStream& cin) {
    decltype(buildGraph(cin)) res;
    auto& nodes = res.first;
    auto& edges = res.second;

    size_t nbNodes;
    cin >> nbNodes;

    nodes.resize(nbNodes);
    for (auto& node: nodes) {
        int bicycle;
        cin >> node.id >> node.longitude >> node.latitude >> bicycle;
        node.isBicycleParking = bicycle;
    }

    edges.resize(nbNodes);
    for (auto& e: edges) {
        size_t nbNeighbors;
        cin >> nbNeighbors;
        e.resize(nbNeighbors);
        for (auto& n: e) {
            cin >> n.first >> n.second;
        }
    }
    return std::move(res); 
}

} // end of namespace osm
