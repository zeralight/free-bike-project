#include <QtCore>
#include <QProcess>
#include <QString>
#include <QTextStream>

#include <iostream>
#include <clocale>
#include <stdexcept>
#include <memory>
#include <cassert>

#include "OsmParser.hpp"
#include "ShortestPaths.hpp"

void usage();
void run(char* const);
int main(int argc, char **argv)
{
    if (argc < 2) {
        usage();
        return 0;
    }
    QCoreApplication app(argc, argv);
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); 
    run(argv[1]);
    return 0;
}

void usage() {
    std::cout << "Usage: ./parser osm-xml-map_path\n";
}

void run(char* const filePath) {
    try {
        // launch xml parser process
        QProcess parserProcess(nullptr);
        parserProcess.start("./xml", QStringList(filePath));
        parserProcess.waitForFinished(-1);

        // read parser output
        auto outputProcess = std::make_unique<QString>(parserProcess.readAllStandardOutput());
        auto inputStream = std::make_unique<QTextStream>(outputProcess.get());
        auto rawGraph = osm::buildGraph(*inputStream);
        auto const& nodes = rawGraph.first;
        auto const& edges = rawGraph.second;
        outputProcess.reset(nullptr);
        inputStream.reset(nullptr);
        // run shortest paths
        auto paths = osm::AllShortestPaths(nodes, edges).run();
        // output results
        osm::printGraphAndShortestPaths(nodes, edges, paths);   
    } catch (std::logic_error const& e) {
        std::cerr << e.what() << '\n';
    }
}


