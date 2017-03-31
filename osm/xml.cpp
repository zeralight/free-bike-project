#include <QtCore>

#include <iostream>
#include <clocale>
#include <stdexcept>

#include "OsmParser.hpp"
#include "ShortestPaths.hpp"

using namespace osm;
void usage();
void run(char* const);

int main(int argc, char **argv)
{
    if (argc < 2) {
        usage();
        return 0;
    }
    QCoreApplication app(argc, argv);
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // Avoid system floatting number representation (like 25,25)
    run(argv[1]);
    return 0;
}

void usage() {
    std::cout << "Usage: ./parser osm-xml-map_path\n";
}

void run(char* const filePath) {
    try {
		QFile file(filePath);
		if (!file.open(QIODevice::ReadOnly))
			throw std::logic_error("Couldn't open the file");
	    osm::OsmParser parser(file);
        auto rawGraph = parser.parse();
        file.close();
        auto& nodes = rawGraph.first;
        auto& edges = rawGraph.second;
        printGraph(nodes, edges);
    } catch (std::logic_error const& e) {
        std::cerr << e.what() << '\n';
    }

}
