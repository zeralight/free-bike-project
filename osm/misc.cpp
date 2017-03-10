#include "misc.hpp"
#include <cmath>
#include <vector>
#include <unordered_map>
#include <limits>
#include <iostream>

namespace osm
{
static constexpr auto EARTH_RADIUS = 6378.137*1000;
static constexpr auto DEG_TO_RAD = M_PI / 180;

double haversineDist(double lat1, double lon1, double lat2, double lon2)
    /*
       Angles: degree
       Result: Meter 
     */
{
    double dx, dy, dz;
    lon1 -= lon2;
    lon1 *= DEG_TO_RAD, lat1 *= DEG_TO_RAD, lat2 *= DEG_TO_RAD;
    dz = std::sin(lat1) - std::sin(lat2);
    dx = std::cos(lon1) * std::cos(lat1) - std::cos(lat2);
    dy = std::sin(lon1) * std::cos(lat1);
    return std::asin(std::sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * EARTH_RADIUS;
}

std::pair<double, double> gpsToCartesian(double latitude, double longitude)
{
    /*
        tulip version
        Angles: degree
        Result, {x, y} in meters
    */
    if(latitude == 90.)
        latitude = 89.999;
    auto mercatorLatitude = latitude*2./360.*M_PI;
    mercatorLatitude = std::sin(std::abs(mercatorLatitude));
    mercatorLatitude = std::log((1.+mercatorLatitude)/(1. - mercatorLatitude))/2.;
    if (latitude < 0)
        mercatorLatitude=0.-mercatorLatitude;
    if (mercatorLatitude*360./M_PI < -360)
        mercatorLatitude =- M_PI;
    
    return {2*longitude, mercatorLatitude*360./M_PI};
}

/*
std::vector<std::vector<std::vector<OsmNode>>> f(std::unordered_map<NodeIndexType, OsmNode> const& nodes) {
    double leftMost = std::numeric_limits<double>::max();
    double rightMost = -leftMost;
    double downMost = leftMost;
    double upMost = rightMost;

    std::unordered_map<NodeIndexType, std::pair<double, double>> ecefCoordinates;
    for (auto const& it: nodes) {
        auto const& node = it.second;
        auto xy = gpsToCartesian(node.latitude, node.longitude);
        ecefCoordinates[node.id] = xy;
        leftMost = std::min(leftMost, xy.first);
        rightMost = std::max(rightMost, xy.first);
        downMost = std::min(downMost, xy.second);
        upMost = std::max(upMost, xy.second);
    }

    
    //constexpr double STEP = 1.;
    size_t xSteps = std::lround(std::sqrt(rightMost - leftMost)) + 1;
    size_t ySteps = std::lround(std::sqrt(upMost - downMost)) + 1;
    std::cout << "xSteps = " << xSteps << ", ySteps = " << ySteps << std::endl;

    std::vector<std::vector<std::vector<NodeIndexType>>> res(ySteps);
    for (auto& v: res)
        v.resize(xSteps);

    for (auto const& it: ecefCoordinates) {
        auto const& node = it.second;
        size_t j = std::lround((node.first - leftMost) / STEP);
        size_t i = std::lround((node.second - downMost) / STEP);
        std::cout << "i = " << i << ", j = " << j << std::endl;
        res[i][j].push_back(it.first);
        std::cout << "done" << std::endl;
    }

    return std::vector<std::vector<std::vector<OsmNode>>>();
}
*/
} // end of namespace osm
