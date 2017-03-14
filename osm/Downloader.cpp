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
    QString polygonStr;
    bool firstTime(true);
    // only "1" bounding polygon is supported
    in >> str1; // polygon first line
    in >> str1; // 1
    for(;;) {
        in >> str1;
        if (str1 == "END") // if not then str is the longitude
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
    request(city+".xml", polygonStr);
}

void Downloader::request(QString const& fileName, QString const& polygonStr) {
    auto url = prepareRequest(polygonStr);
    sendRequest(url, fileName);
}

QString Downloader::prepareRequest(QString const& polygonStr) {
    auto query =
    QString("(\n (\n") + 
        "  node[amenity=bicycle_rental](poly:'" + polygonStr + "');\n" + // bicycle nodes
        "  way[amenity=bicycle_rental](poly:'" + polygonStr + "');\n" + // bicycle ways
        "  way[highway](poly:'" + polygonStr + "');\n" + // highways
        "  way[junction](poly:'" + polygonStr + "');\n" + // junctions
    "  );\n >;\n); out meta;";

    QString baseUrl = "http://overpass-api.de/api/interpreter?data=";

    return query;
}

void Downloader::sendRequest(QString const& query, QString const& fileName){
    QEventLoop eventLoop;

    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl baseUrl("http://overpass-api.de/api/interpreter");
    QUrl params;
    params.addQueryItem("data", query);

    QNetworkRequest req{baseUrl};
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkReply *reply = mgr.post(req, params.encodedQuery());
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Success\n";
        QFile output(fileName);
        output.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream ts(&output);
        ts << reply->readAll();
        output.close();
        qDebug() << "Output to " + fileName + '\n';
    }
    else {
        qDebug() << "Failure: " << reply->errorString();
    }

    delete reply;
}

} // end of namespace dll
