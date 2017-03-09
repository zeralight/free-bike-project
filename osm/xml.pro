SOURCES += xml.cpp OsmParser.cpp InternalNode.cpp misc.cpp

QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -DDEBUG_ONLY_PROCESSED_NODES
QMAKE_CXXFLAGS += -DDEBUG_MISSING_PATHS
#QMAKE_CXXFLAGS += -DDEBUG_VELO

CONFIG += console

QT -= gui

# install
target.path = .
INSTALLS += target
