#ifndef DOWNLOADER_HPP
#define DOWNLOADER_HPP
#include <vector>

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
    void request(QString const& fileName, std::vector<QString> const& boundingPolygonStr);
    QString prepareRequest(std::vector<QString> const& polygonStr);
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
};

} // end of namespace dll
#endif
