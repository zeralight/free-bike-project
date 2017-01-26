#include "InternalNode.hpp"

namespace osm {
Node::Node(): _idRead(false), _latitudeRead(false), _longitudeRead(false), 
            _amenityKey(false), _bicycleParkingValue(false) {}
    
    void Node::setId(NodeIndexType id) {
        _id = id;
        _idRead = true;
    }
    
    void Node::setLatitude(double latitude) {
        _latitude = latitude;
        _latitudeRead = true;
    }

    void Node::setLongitude(double longitude) {
        _longitude = longitude;
        _longitudeRead = true;
    }

    void Node::setAmenityKey() { _amenityKey = true; }
    
    void Node::setBicycleParkingValue() { _bicycleParkingValue = true; }

    void Node::reset() {
        _idRead = false;
        _latitudeRead = false;
        _longitudeRead = false;
        _amenityKey = false;
        _bicycleParkingValue = false;
    }

    bool Node::hasId() const { return _idRead; }

    bool Node::hasLongitude() const { return _longitudeRead; }

    bool Node::hasLatitude() const { return _latitudeRead; }
    
    bool Node::validState() const { return _idRead && _latitudeRead && _longitudeRead; }

    NodeIndexType Node::id() const { return _id; }

    double Node::longitude() const { return _longitude; }

    double Node::latitude() const { return _latitude; }

    double Node::isBicycleParking() const { return _amenityKey && _bicycleParkingValue; }
} // end of namespace osm
