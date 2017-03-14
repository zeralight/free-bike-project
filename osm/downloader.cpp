#include <QCoreApplication>
#include <QDebug>

#include <iostream>
#include <string>
#include <array>
#include <string>

#include "Downloader.hpp"

using namespace osm;

void usage() {
    std::cout << "Usage:\n"
                << "downloader city_name\n";
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    if (argc < 1) {
        std::cerr << "not enough args\n";
        usage();
        return 0;
    }
    QString cityName = argv[1];
    Downloader downloader;
    downloader.download(cityName);

    return 0;
}
