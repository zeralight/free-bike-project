#ifndef NODE_HPP
#define NODE_HPP
#include "InternalNode.hpp"

namespace osm {
/**
 * @ingroup osm
 * @brief This class represents an node in the OpenStreetMap
 */
struct OsmNode {
    NodeIndexType id;
    double longitude;
    double latitude;
    /**
     * @brief holds true if the node is a bicycle parking
     */
    bool isBicycleParking;
    /**
     * @brief Default constructor
     * @param n The corresponding InternalNode to the osm node
     */
    OsmNode(Node const &n = Node()): id(n.id()), longitude(n.longitude()),
        latitude(n.latitude()), isBicycleParking(n.isBicycleParking()) {}

    friend bool operator==(OsmNode const& lhs, OsmNode const& rhs) {
        return (lhs.id == rhs.id);
    }
    
    struct Hasher {
        std::size_t operator()(OsmNode const& n) const {
            return std::hash<NodeIndexType>()(n.id);
        }
    };
     
};



} // end of namespace osm
#endif
