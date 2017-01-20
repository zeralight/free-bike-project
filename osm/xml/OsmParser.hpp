#ifndef OSM_PARSER_HPP
#define OSM_PARSER_HPP
#include <unordered_map>
#include <vector>

#include <QXmlStreamReader>
#include <QFile>
#include <QTextStream>

#include "InternalNode.hpp"
#include "Node.hpp"

namespace osm {

using OsmGraph = std::unordered_map<NodeIndexType, std::pair<OsmNode, std::unordered_map<NodeIndexType, double>>>;
/*
    graph -> OsmGraph
    graph[node_id].first -> OsmNode (node_id, longitude, latitude, isBicycleParking)
    graph[node_id].second -> { node2_id /  there is a vertex between node_id and node2_id }
    graph[node_id].second[node2_id] -> distance(which should be the haversine distance) between node_id and node2_id
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
	
	public:
	OsmParser(QFile &file);
	
	OsmGraph parse();
	bool ready() const;
};

} // end of namespace osm
#endif
