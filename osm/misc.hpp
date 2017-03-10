#ifndef DEF_MISC_HPP
#define DEF_MISC_HPP
#include <QTextStream>

#include <vector>
#include <unordered_map>

#include "Node.hpp"

namespace osm {
/**
 * @ingroup osm
 * @brief Calculates the haversine distance between 2 points in meters and return it
*/
double haversineDist(double latitude1, double longitude1, double latitude2, double longitude2);

/**
 * @ingroup osm
 * @brief Make a Mercator projection
 * @param latitude latitude of the point
 * @param longitude longitude of the point
 * @return Mercator projection (x, y)
*/
std::pair<double, double> gpsToCartesian(double latitude, double longitude);
} // end of namespace osm
#endif
