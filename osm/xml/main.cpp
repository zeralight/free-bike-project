#include <QtCore>
#include <QString>
#include <QXmlStreamReader>

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <clocale>
#include <stdexcept>

#include "OsmParser.hpp"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // Avoid system floatting number representation (like 25,25)
    try {
		QFile file("../map.xml");
		if (!file.open(QIODevice::ReadOnly))
			throw std::logic_error("Couldn't open the file");
	    osm::OsmParser parser(file);
	    parser.parse();
    } catch (std::logic_error const& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
