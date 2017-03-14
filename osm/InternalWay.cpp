#include "InternalWay.hpp"

namespace osm {
Way::Way(): _idRead(false), _id(0), _highwayKey(false),
            _amenityKey(false), _bicycleParkingValue(false) {}
   
    void Way::setId(WayIndexType id) { _id = id; _idRead = true; }

    void Way::setHighwayKey() { _highwayKey = true; }
    
    void Way::setAmenityKey() { _amenityKey = true; }
    
    void Way::setBicycleParkingValue() { _bicycleParkingValue = true; }

    void Way::setFreeParkingKey() { _freeParkingKey = true; }

    void Way::setFreeParkingValue() { _freeParkingValue = true; }

    void Way::updateStatus() {
        if ( !(_amenityKey && _bicycleParkingValue) ) {
            _amenityKey = false;
            _bicycleParkingValue = false;
        }
    }

    void Way::reset() {
        _idRead = false;
        _id = 0;
        _highwayKey = false;
        _amenityKey = false;
        _bicycleParkingValue = false;
    }

    bool Way::hasId() const { return _idRead; }

    WayIndexType Way::id() const { return _id; }

    bool Way::isHighway() const { return _highwayKey; }

    bool Way::isBicycleParking() const {
        return _amenityKey 
            && _bicycleParkingValue;
        }
} // end of namespace osm
