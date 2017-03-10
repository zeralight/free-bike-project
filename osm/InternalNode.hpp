#ifndef OSM_NODE_HPP
#define OSM_NODE_HPP

namespace osm {
using NodeIndexType = unsigned long long;

/**
 * @ingroup osm
 * @brief this class is used to process the xml output of the Downloader
 * it is strictly used by the OSM Parser
 */
class Node {
    private:
    bool _idRead;
    bool _latitudeRead;
    bool _longitudeRead;

    NodeIndexType _id;
	double _latitude;
	double _longitude;
    bool _amenityKey;
    bool _bicycleParkingValue;

    public:
    Node();
    
    void setId(NodeIndexType id);
    
    void setLatitude(double latitude);

    void setLongitude(double longitude);

    void setAmenityKey();
    
    void setBicycleParkingValue();

    void reset();

    bool hasId() const;

    bool hasLongitude() const;

    bool hasLatitude() const;
    
    bool validState() const;

    NodeIndexType id() const;

    double longitude() const;

    double latitude() const;

    double isBicycleParking() const;
};

} // end of namespace osm
#endif
