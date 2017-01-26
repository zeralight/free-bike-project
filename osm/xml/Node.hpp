#ifndef NODE_HPP
#define NODE_HPP
#include "InternalNode.hpp"

namespace osm {
struct OsmNode {
    NodeIndexType id;
    double longitude;
    double latitude;
    bool isBicycleParking;
    OsmNode(Node const &n = Node()): id(n.id()), longitude(n.longitude()),
        isBicycleParking(n.isBicycleParking()) {}

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
