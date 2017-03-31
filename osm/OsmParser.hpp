#ifndef OSM_PARSER_HPP
#define OSM_PARSER_HPP
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include <QXmlStreamReader>
#include <QFile>
#include <QTextStream>

#include "InternalNode.hpp"
#include "Node.hpp"

namespace osm {
/**
    public
**/
using Nodes = std::vector<OsmNode>;
using AdjacencyList = std::vector<std::vector<std::pair<size_t, double>>>;

/**
    private
*/
// OsmGraph is internal
using OsmGraph = std::unordered_map<NodeIndexType, std::pair<OsmNode, std::unordered_map<NodeIndexType, double>>>;
/*
    graph -> OsmGraph
    graph[node_id].first -> OsmNode (node_id, longitude, latitude, isBicycleParking)
    graph[node_id].second -> { node2_id /  there is a vertex between node_id and node2_id }
    graph[node_id].second[node2_id] -> distance(which should be the haversine distance) between node_id and node2_id
*/

/**
 * @ingroup osm
 * @brief This class is used to parse the xml file downloaded from OpenStreetMap
 */
class OsmParser {
	private:
	enum class State {
		osm,
		node,
		way,
		nd,
		tag
	};

	QXmlStreamReader reader;
	bool _ready;
	
    class ClosestPoints {
        private:
        struct comparator {
            bool operator()(std::pair<NodeIndexType, double> const& lhs,
                            std::pair<NodeIndexType, double> const& rhs) {
                return (lhs.second < rhs.second);
            }
        };

        using NodesType = std::unordered_map<NodeIndexType, OsmNode>;
        using ConnectedNodesType = std::unordered_set<NodeIndexType>;
        NodesType const& _nodes;
        ConnectedNodesType const& _connectedNodes;
        size_t const& _count;

        static size_t xxx;
        public:
        using result_type = std::pair<NodeIndexType, std::vector<NodeIndexType>>;
        ClosestPoints(NodesType const& nodes, ConnectedNodesType const& connectedNodes, size_t count);
        std::pair<NodeIndexType, std::vector<NodeIndexType>> operator()(NodeIndexType const& bicycleNode) const;
    };
    public:
	/**
     * @brief configure the parser with the associated map
     * @param file The file which the parser shall work on
     */
    OsmParser(QFile &file);
	
	/**
     * @ingroup This is the main method of the class: makes the parsing
     * @return (liste of nodes, adjacency list)
     */
    std::pair<Nodes, AdjacencyList> parse();
    /**
     * @brief return true only if the parser can run without error
     */ 
    bool ready() const;
};

// utility functions to pipe result between processes
/**
 * @ingroup osm
 * @brief print parameters to standard output
 * The output shall be used later by another process the consume the data 
 */
void printGraph(Nodes const& nodes, AdjacencyList const& edges);
/**
 * @ingroup osm
 * @brief extract nodes and adjacency list from the input
 */
std::pair<Nodes, AdjacencyList> buildGraph(QTextStream& input);
} // end of namespace osm
#endif
