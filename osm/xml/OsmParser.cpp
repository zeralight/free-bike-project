#include <unordered_map>
#include <vector>
#include <stack>
#include <stdexcept>
#include <cmath>

#include <QXmlStreamReader>

#include "OsmParser.hpp"
#include "InternalNode.hpp"
#include "Node.hpp"


#define DEBUG_VELO

namespace osm {

double haversine_dist(double lat1, double lon1, double lat2, double lon2)
/*
    Angles: degree
    Result: Kilometer
*/
{
    constexpr auto R = 6371.8;
    constexpr auto TO_RAD = 3.1415926536 / 180;
    double dx, dy, dz;
    lon1 -= lon2;
    lon1 *= TO_RAD, lat1 *= TO_RAD, lat2 *= TO_RAD;
    dz = std::sin(lat1) - std::sin(lat2);
    dx = std::cos(lon1) * std::cos(lat1) - std::cos(lat2);
    dy = std::sin(lon1) * std::cos(lat1);
    return std::asin(std::sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R;
}

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

OsmGraph OsmParser::parse() {
	if (!_ready)
		throw std::logic_error("Parser not ready");

	std::unordered_map<NodeIndexType, OsmNode> nodes;
	std::vector<std::vector<NodeIndexType>> ways;

#ifdef DEBUG_VELO
	QTextStream out(stdout);
#endif

	std::stack<State> state;
	NodeIndexType ndId;
	Node node;
	std::vector<NodeIndexType> way;
	while (!reader.hasError() && !reader.atEnd()) {
		reader.readNext();
		//out << reader.name().toString() << endl;
		if (reader.isStartElement()) {
			auto const &name = reader.name().toString();
			//out << "<" << reader.name().toString() << ">" << endl;
			
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
				//out << e.name().toString() << '=' << e.value().toString() << endl;
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
			//out << "</" << reader.name().toString() << ">" << endl;

			if (name == tagNode && !state.empty() && state.top() == State::node) { // </node> 
				//out << node.hasId() << ' ' << node.hasLongitude() << ' ' << node.hasLatitude() << '\n';
				if (node.validState()) {
					nodes.insert({node.id(), OsmNode(node)});
					//nodes[node.id()] = node;
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

#ifdef DEBUG_VELO
	size_t nbBicycleParkings = 0;
	out << "\n-----------------------------------------------------------\n";
	out << "Nodes:\n";
	for (auto const &node: nodes) {
		out << node.first << ' ' << node.second.latitude << ' ' 
			<< node.second.longitude << ' ' << node.second.isBicycleParking << '\n';
		if (node.second.isBicycleParking)
			++nbBicycleParkings;
	}
	out << "\n\n--------------------------------------\nWays:\n";
	for (auto const &way: ways) {
		out << "-------------------------------------------------\n";
		for (auto const &nd: way)
			out << nd << ' ';
		out << '\n';
	}
	out << "--------------------------------\n\n";
	out << "There are " << nodes.size() << " nodes, " << ways.size() << " ways and " << nbBicycleParkings << " bicycle parkings\n";
	out << "\n\n";
#endif
	_ready = false;

    OsmGraph res;

    for (auto const &w: ways) {
        for (size_t i = 0; i+1 < w.size(); ++i) {
            auto const& node1 = nodes[w[i]];
            auto const& node2 = nodes[w[i+1]];

            double dist = haversine_dist(node1.latitude, node1.longitude, node2.latitude, node2.longitude);
            res[node1.id].first = node1;
            res[node2.id].first = node2;
            res[node1.id].second[node2.id] = dist;
            res[node2.id].second[node1.id] = dist;
        }
    }

    return res;
}

} // end of namespace osm
