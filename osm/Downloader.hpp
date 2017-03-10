#ifndef DOWNLOADER_HPP
#define DOWNLOADER_HPP
#include <array>

#include <QString>
#include <QHash>

namespace osm {
/** 
 * @ingroup osm
 * @brief This class is used to download OpenStreetMap maps
 * use the download method to get some city or region map
 */
class Downloader {
    private:
    /**
     * @brief holds all the known cities with their bounding boxes
     */
    QHash<QString, std::array<double, 4>> citiesBoundingBoxes;
    void request(QString const& fileName, std::array<double, 4> const& boundingBox);
    QString prepareRequest(std::array<double, 4> const& boundingBox);
    void sendRequest(QString const& url, QString const& fileName);
    public:
    Downloader();
    /**
     * @brief Gets a city map
     * The city must be predefined in the implementation
     * @param city The city name
     * The output file name is the city name suffixed with .xml
     */
    void download(QString const& city);
    /**
     * @brief Gets a bounding-box map
     * @param boundingBox the tuple (minimum longitude, minimum latitude, maximum longitude, maximum latitude) of the region
     * @param outputFileName the path where the map will be stored
     */
    void download(std::array<double, 4> const& boundingBox, QString const& outputFileName);
};

} // end of namespace dll
#endif
