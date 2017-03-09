SOURCES += test_shortest_paths.cpp ../ShortestPaths.cpp ../OsmParser.cpp ../InternalNode.cpp ../misc.cpp 
INCLUDEPATH += ..
QT -= gui
QMAKE_CXXFLAGS += -std=c++14
#QMAKE_CXXFLAGS += -DDEBUG_ONLY_PROCESSED_NODES

CONFIG += console

# install
target.path = .
INSTALLS += target
