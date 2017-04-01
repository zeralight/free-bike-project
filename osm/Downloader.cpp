#include "Downloader.hpp"

#include <stdexcept>
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>

#include <iostream>

namespace osm {

QString const POLYGONS_DIR = "./polygons";

Downloader::Downloader() {}

void Downloader::download(QString const& city) {
    auto path = POLYGONS_DIR + "/" + city + ".py";
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly))
        throw std::logic_error("Couldn't Open the file: " + path.toStdString());
    
    QTextStream in(&f);
    QString str1, str2;
    std::vector<QString> polygonStrings;
    in >> str1; // first line : "polygon"
    if (str1 != "polygon")
        throw std::logic_error("Parsing Error at Line 1: Expected polygon: " + city.toStdString());
    for(;;) {
        in >> str1;
        if (str1 == "END") // if not then it is the polygon index
            break;
        QString polygonStr;
        bool firstTime(true);
        for(;;) {
            in >> str1;
            if (str1 == "END") // if not then it is the 1st point longitude
                break;
            in >> str2; // latitude;
            if (!firstTime)
                polygonStr += ' ';
            else
                firstTime = false;
            polygonStr += str2;
            polygonStr += ' ';
            polygonStr += str1;
        }
        polygonStrings.push_back(std::move(polygonStr));
    }
    request(city+".xml", polygonStrings);
}

void Downloader::request(QString const& fileName, std::vector<QString> const& polygonStr) {
    auto url = prepareRequest(polygonStr);
    sendRequest(url, fileName);
}

QString Downloader::prepareRequest(std::vector<QString> const& polygonsStrings) {
    std::vector<QString> const acceptedHighways = {
        "motorway",
        "motorway_link",
        "trunk",
        "trunk_link",
        "primary",
        "primary_link",
        "secondary",
        "secondary_link",
        "residential",
        "residential_link",
        "service",
        "tertiary",
        "tertiary_link",
        "road",
        "unclassified",
        "living_street",
        // "private",
        // "footway",
        // "steps",
        // "bridleway",
        // "construction",
        "cycleway",
        "path",
        // "bus_guideway"
    };

    QString highwaysQuery;
    for (auto const& s: acceptedHighways)
        highwaysQuery += "way[highway='"+s+"'](poly:'%1');";
    
    auto querySinglePolygon = QString{} +
        "  node[amenity=bicycle_rental](poly:'%1');\n" + // bicycle nodes
        "  way[amenity=bicycle_rental](poly:'%1');\n" + // bicycle ways
        //"  way[highway](poly:'%1');\n"; // highways
        highwaysQuery; // highways

    QString query = "((";
    for (auto const& str: polygonsStrings) {
        query += querySinglePolygon.arg(str);
    }
    query += "); >; ); out meta;";
    std::cerr << "QUERY = \n" << query.toStdString() << '\n';
    return query;
}

void Downloader::sendRequest(QString const& query, QString const& fileName){
    QEventLoop eventLoop;

    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl baseUrl("http://api.openstreetmap.fr/oapi/interpreter");
    //QUrl baseUrl("http://overpass-api.de/api/interpreter");
    QUrl params;
    params.addQueryItem("data", query);

    QNetworkRequest req{baseUrl};
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkReply *reply = mgr.post(req, params.encodedQuery());
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QFile output(fileName);
        output.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream ts(&output);
        //ts << reply->readAll(); // might consume a lot of memory
        while (reply->bytesAvailable() > 0) {
            ts << reply->read(10*1024*1024);
            std::cerr << "Read Data\n";
        }
        output.close();
        qDebug() << "Output to " + fileName + '\n';
    }
    else {
        qDebug() << "Failure: " << reply->errorString();
    }

    delete reply;
}

} // end of namespace dll
