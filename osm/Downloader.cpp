#include "Downloader.hpp"

#include <stdexcept>
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>

namespace osm {

Downloader::Downloader() {    
    /*
       Bounding box must follow the format min_longitude, min_latitude, max_longitude, max_latitude
     */

    // Talence
    citiesBoundingBoxes.insert(QString("talence"), {-0.638973,44.810752,-0.533309,44.916704});
}

void Downloader::download(QString const& city) {
    if (citiesBoundingBoxes.contains(city))
        request(city+".xml", citiesBoundingBoxes[city]);
    else
        throw std::logic_error("city not recognized");
}

void Downloader::download(std::array<double, 4> const& boundingBox, QString const& outputFileName) {
    request(outputFileName, boundingBox);
}

void Downloader::request(QString const& fileName, std::array<double, 4> const& boundingBox) {
    auto url = prepareRequest(boundingBox);
    sendRequest(url, fileName);
}

QString Downloader::prepareRequest(std::array<double, 4> const& args) {
    //QString baseUrl = "http://overpass.osm.rambler.ru/cgi/xapi_meta"; // Might be not the best one 
    QString baseUrl = "http://overpass-api.de/api/interpreter";

    std::array<QString, 4> strArgs;
    for (int i = 0; i < 4; ++i) strArgs[i] = QString::number(args[i]);

    //QString fullUrl = baseUrl + "?*[bbox=" + strArgs[0] + "," + strArgs[1] + "," + strArgs[2] + "," + strArgs[3] + "]"; // old way
    QString fullUrl = baseUrl + "?data="
        + "node("+strArgs[1]+","+strArgs[0]+","+strArgs[3]+","+strArgs[1]+");"
        + "out;"
        + "way("+strArgs[1]+","+strArgs[0]+","+strArgs[3]+","+strArgs[1]+");"
        + "out;";
    qDebug() << "url = " << fullUrl << '\n';
    return fullUrl;
}

void Downloader::sendRequest(QString const& url, QString const& fileName){
    QEventLoop eventLoop;

    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkRequest req{ QUrl( url ) };
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Success\n";
        QFile output(fileName);
        output.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream ts(&output);
        ts << reply->readAll();
        output.close();
        qDebug() << "Output to map.xml\n";
    }
    else {
        qDebug() << "Failure" << reply->errorString();
    }

    delete reply;
}

} // end of namespace dll
