#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>

#include <iostream>
#include <string>
#include <array>

void usage();
void sendRequest(QString const& url);
QString prepareRequest(std::array<double, 4> const& args);

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // Avoid system floatting number representation (like 25,25) 
    
    if (argc < 5) {
        qDebug() << "not enough args\n";
        usage();
        return 0;
    }

    std::array<double, 4> args;
    for (int i = 1; i <= 4; ++i) {
        char* error;
        args[i-1] = std::strtod(argv[i], &error);
        if (*error != '\0') {
            qDebug() << argv[i] << " is not a valid number\n";
            qDebug() << *error << '\n';
            usage();
            return 0;
        }
    }

    auto request = prepareRequest(args);
        
    sendRequest(request);
    return app.exec();
}

void sendRequest(QString const& url){
    // create custom temporary event loop on stack
    QEventLoop eventLoop;
 
    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
 
    // the HTTP request
    QNetworkRequest req{ QUrl( url ) };
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Success\n";
        QFile output("map.xml");
        output.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream ts(&output);
        ts << reply->readAll();
        output.close();
        std::cout << "Output to map.xml\n";
    }
    else {
        qDebug() << "Failure" << reply->errorString();
    }

    delete reply;
}

QString prepareRequest(std::array<double, 4> const& args) {
    QString baseUrl = "http://overpass.osm.rambler.ru/cgi/xapi_meta"; // Might be not the best one 
    
    std::array<QString, 4> strArgs;
    for (int i = 0; i < 4; ++i) strArgs[i] = QString::number(args[i]);

    QString fullUrl = baseUrl + "?*[bbox=" + strArgs[0] + "," + strArgs[1] + "," + strArgs[2] + "," + strArgs[3] + "]";
    qDebug() << "url = " << fullUrl << '\n';
    return fullUrl;
}

void usage() {
    std::cout << "Usage:\n"
            << "downloader left bottom right top\n"
            << "downloader min_longitude min_latitude max_longitude max_latitude\n";
}
