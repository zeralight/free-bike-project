#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <cassert>
#include <iostream>
#include <memory>

#include <QXmlStreamReader>
#include <QtConcurrentMap>

#include "OsmParser.hpp"
#include "InternalNode.hpp"
#include "InternalWay.hpp"
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
QString const attrWayId = "id";
QString const attrTagKey = "k";
QString const attrTagVal = "v";

QString const valAmenity = "amenity";
QString const valBicycleParking = "bicycle_rental";
QString const valHighway = "highway";
QString const valJunction = "junction";

std::vector<QString> const acceptedHighways = {
    "motorway",
    "motorway_link",
    "trunk",
    "trunk_link",
    "primary",
    "primary_link",
    "secondary",
    "secondary_link",
    "residential",
    "residential_link",
    "service",
    "tertiary",
    "tertiary_link",
    "road",
    "unclassified",
    "living_street",
    "cycleway",
    "path",
    // "private",
    // "footway",
    // "steps",
    // "bridleway",
    // "construction",
    // "bus_guideway"
};
size_t OsmParser::ClosestPoints::xxx = 0;
OsmParser::OsmParser(QFile &file) : reader(&file), _ready(true) {}

std::pair<Nodes, AdjacencyList> OsmParser::parse() {
	if (!_ready)
		throw std::logic_error("Parser not ready");

    // allocating explictly containers on heap to release them as soon as possible
    auto pNodes = std::make_unique<std::unordered_map<NodeIndexType, OsmNode>>(); 
    auto pWays = std::make_unique<std::vector<std::vector<NodeIndexType>>>(); 
    auto pOrderedNodes = std::make_unique<std::vector<NodeIndexType>>(); 
    auto pNodesPosInOrderedNodes = std::make_unique<std::unordered_map<NodeIndexType, size_t>>(); 
    auto pFutureBicycleNodes = std::make_unique<std::vector<NodeIndexType>>();

    auto& nodes = *pNodes;
    auto& ways = *pWays;
    auto& orderedNodes = *pOrderedNodes;
    auto& nodesPosInOrderedNodes = *pNodesPosInOrderedNodes;
    auto& futureBicycleNodes = *pFutureBicycleNodes;

#ifdef DEBUG_VELO
#warning "DEBUG_VELO is set"
#endif

    std::stack<State> state;
    NodeIndexType ndId;
    Node node;
    Way wayState;
    std::vector<NodeIndexType> way;
    bool parsingNode = false;
    bool parsingWay = false;
    while (!reader.hasError() && !reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            auto const &name = reader.name().toString();
            if (name == tagNode && !state.empty() && state.top() == State::osm) { // <osm><node>
                state.push(State::node);
                parsingNode = true;
            }
            else if (name == tagWay && !state.empty() && state.top() == State::osm) { // <osm><way>
                state.push(State::way);
                parsingWay = true;
            }
			else if (name == tagNd && !state.empty() && state.top() == State::way) { // <osm><way><nd>
				state.push(State::nd);
			}
			else if (name == tagOsm && state.empty()) {
				state.push(State::osm);
			}
			else if (name == tagTag && !state.empty() 
                    && (state.top() == State::node || state.top() == State::way)) { // <osm><node><tag>
				state.push(State::tag);
			}
			else { // Ignore everything else
				reader.readElementText(QXmlStreamReader::SkipChildElements);
				continue;
			}

			auto const &attrs = reader.attributes();
			for (auto const &e: attrs) {
				auto const &eName = e.name().toString();
				auto const &eValue = e.value().toString();
				if (eName == attrNodeId && state.top() == State::node) { // <node id=..>
				   node.setId(std::stoul(eValue.toStdString())); 
				}
                else if (eName == attrWayId && state.top() == State::way) { // <way id=..>
                    wayState.setId(std::stoul(eValue.toStdString()));
                }
				else if (eName == attrNodeLat && !state.empty() && state.top() == State::node) { // <node lat=..>
                    node.setLatitude(std::stod(eValue.toStdString()));
				}
				else if (eName == attrNodeLon && !state.empty() && state.top() == State::node) { // <node lon=..>
					node.setLongitude(std::stod(eValue.toStdString()));
				}
				else if (eName == attrNdRef && !state.empty() && state.top() == State::nd) { // <way><nd ref="..">
					ndId = std::stoul(eValue.toStdString());
				}
                //else if (eName == attrTagKey && (eValue ==  valHighway /*|| eValue == valJunction */)
                else if (eName == attrTagKey 
                        && !state.empty() && state.top() == State::tag && parsingWay) { // <tag k="highway">
                    wayState.setHighwayKey();
                }
				else if (eName == attrTagKey && eValue == valAmenity
						&& state.top() == State::tag) { // <tag k="amenity">
                    if (parsingNode)
					    node.setAmenityKey();
				    else if (parsingWay)
                        wayState.setAmenityKey();
                }
				else if (eName == attrTagVal && eValue == valBicycleParking
						&& state.top() == State::tag) { // <tag v="bicycle_rental">
					if (parsingNode)
                        node.setBicycleParkingValue();
				    else if (parsingWay)
                        wayState.setBicycleParkingValue();
                }
            }
            node.updateStatus();
            wayState.updateStatus();
		}
		else if (reader.isEndElement()) {
            auto const &name = reader.name().toString();
            
            if (name == tagNode && !state.empty() && state.top() == State::node) { // </node> 
            	if (node.validState()) {
            		nodes.insert({node.id(), OsmNode(node)});
            		orderedNodes.push_back(node.id());
                    nodesPosInOrderedNodes[node.id()] = orderedNodes.size()-1;
            	} 
            	state.pop();
            	node.reset();
                parsingNode = false;
            }
            else if (name == tagWay && !state.empty() && state.top() == State::way) { // </way> 
            	// add only road ways
                if (wayState.isHighway()) {
                    ways.push_back(way);
                }
                if (wayState.isBicycleParking()) 
                    futureBicycleNodes.push_back(way.front());
            	way.clear();
                wayState.reset();
            	state.pop();
                parsingWay = false;
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

{
    // ------------------------------ DRAFT
    for (auto const& w: ways) {
        for (auto const& n: w) {
            assert (nodes.find(n) != std::end(nodes));
        }
    }
}
    /*
        for each bicycle parking way, assign a bicycle parking way
    */
    for (auto const& n: futureBicycleNodes) {
        nodes[n].isBicycleParking = true;
    }
    pFutureBicycleNodes.reset(nullptr);
    //  list all bicycle stations
    std::unordered_set<NodeIndexType> bicycleNodes;
    for (auto const& n: nodes) {
        if (n.second.isBicycleParking) {
            bicycleNodes.insert(n.first);
        }
    }
{
    std::cerr << "parsing done\n";
    std::cerr << "total nodes " << nodes.size() << '\n';
    std::cerr << "total ways " << ways.size() << '\n';
    std::cerr << "bicycle nodes " << bicycleNodes.size() << '\n';
}
    /*
        remove non bicycleStations having 0 edge
        Remove this bloc of code once tested on every map
    */
    auto pConnectedNodes = std::make_unique<std::unordered_set<NodeIndexType>>();
    auto& connectedNodes = *pConnectedNodes;
    for (auto const& w: ways) {
        for (auto const& n: w) 
            connectedNodes.insert(n);
    }
{
    // ---------------------------- DRAFT
    for (auto const& n: connectedNodes) {
        assert (nodes.find(n) != std::end(nodes));
    }
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
{
    
    std::cerr << "END OF Removal\n";
    std::cerr << "total nodes " << nodes.size() << '\n';
    std::cerr << "total ways " << ways.size() << '\n';
    std::cerr << "bicycle nodes " << bicycleNodes.size() << '\n';
}
    /*
        End of to-remove code
    */

    /*
        need to speed up the algorithm
        currently it is O((bicycleNodes.size() * connectedNodes.size()) / (Number of Threads))
    */
    {
        auto constexpr L = 1;
        ClosestPoints cp{nodes, connectedNodes, L};
        auto calculations = QtConcurrent::mapped(bicycleNodes, cp);
        calculations.waitForFinished();
        for (auto const& chunk: calculations) {
            auto const& src = chunk.first;
            if (!chunk.second.empty()) {
                connectedNodes.insert(src);
                for (auto const& dest: chunk.second) {
                    ways.push_back({src, dest});
                }
            }
        }
        /*
           for (auto const& n: bicycleNodes) {
           struct comparator {
           bool operator()(std::pair<NodeIndexType, double> const& lhs,
           std::pair<NodeIndexType, double> const& rhs) {
           return (lhs.second < rhs.second);
           }
           };
           if (connectedNodes.find(n) == std::end(connectedNodes)) {
           std::set<std::pair<NodeIndexType, double>, comparator> queue;
           for (auto const& nd: connectedNodes) {
           auto const& node = nodes.at(nd);
           double distance = haversineDist(nodes[n].latitude, nodes[n].longitude,
           node.latitude, node.longitude);
           queue.insert({node.id, distance});
           if (queue.size() > L)
           queue.erase(--std::end(queue));
           }
           for (auto const& node: queue) {
           ways.push_back({n, node.first});
// std::cerr << "NEW WAY: " << n << ' ' << node.first << '\n';
}
connectedNodes.insert(n);
}
}
        */
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
            double dist = haversineDist(node1.latitude, node1.longitude, node2.latitude, node2.longitude);
            edges[mapper[node1.id]].push_back({mapper[node2.id], dist});
            edges[mapper[node2.id]].push_back({mapper[node1.id], dist});
        }
    }

{
    // ---------------- TO REMOVE
    for (auto const& n: bicycleNodes) {
        assert (!edges[mapper[n]].empty());
    }
}
    return {std::move(finalNodes), std::move(edges)};
}

// ClosestPoints Implementation
OsmParser::ClosestPoints::ClosestPoints(std::unordered_map<NodeIndexType,
                        OsmNode> const& nodes,
                        std::unordered_set<NodeIndexType> const& connectedNodes,
                        size_t count): 
                        _nodes(nodes),
                        _connectedNodes(connectedNodes),
                        _count(count)
    {}

std::pair<NodeIndexType, std::vector<NodeIndexType>>
OsmParser::ClosestPoints::operator()(NodeIndexType const& nodeId) const {
    std::pair<NodeIndexType, std::vector<NodeIndexType>> res;
    res.first = nodeId;
    if (_connectedNodes.find(nodeId) == std::end(_connectedNodes)) {
        std::set<std::pair<NodeIndexType, double>, comparator> queue;
        auto const& node = _nodes.at(nodeId);
        for (auto const& otherNodeId: _connectedNodes) {
            auto const& otherNode = _nodes.at(otherNodeId);
            double distance = haversineDist(otherNode.latitude, otherNode.longitude,
                                            node.latitude, node.longitude);
            queue.insert({otherNodeId, distance});
            if (queue.size() > _count)
                queue.erase(--std::end(queue));
        }
        for (auto const& node: queue) {
            res.second.push_back(node.first);
        }
    }
    return res;
}

// utility functions to pipe results
void printGraph(Nodes const& nodes, AdjacencyList const& edges) {
    using std::cout;
    cout << nodes.size() << '\n';
    for (auto const& node: nodes) {
        cout << node.id << ' ' << node.longitude << ' ' << node.latitude << ' ' << node.isBicycleParking << '\n';
    }
    
    size_t i = 0;
    for (auto const& e: edges) {
        cout << e.size() << '\n';
        for (auto const& neighbor: e) {
            cout << neighbor.first << ' ' << neighbor.second << '\n';
        }
        ++i;
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
