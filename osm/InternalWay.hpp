#ifndef OSM_WAY_HPP
#define OSM_WAY_HPP

namespace osm {
using WayIndexType = unsigned long long;
/**
 * @ingroup osm
 * @brief this class is used to process the xml output of the Downloader
 * it is strictly used by the OSM Parser
 */
class Way {
    private:
    bool _idRead;
    WayIndexType _id;

    bool _highwayKey;
    bool _amenityKey;
    bool _bicycleParkingValue;
    bool _freeParkingKey;
    bool _freeParkingValue;

    public:
    Way();
   
    void setId(WayIndexType);
     
    void setHighwayKey();

    void setAmenityKey();
    
    void setBicycleParkingValue();

    void setFreeParkingKey();

    void setFreeParkingValue();

    void updateStatus();

    void reset();

    bool hasId() const;
    
    WayIndexType id() const;

    bool isHighway() const;

    bool isBicycleParking() const;
};

} // end of namespace osm
#endif
