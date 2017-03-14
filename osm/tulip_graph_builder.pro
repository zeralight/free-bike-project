SOURCES += tulip_graph_builder.cpp ShortestPaths.cpp OsmParser.cpp InternalNode.cpp InternalWay.cpp misc.cpp
QT -= gui
QMAKE_CXXFLAGS += \$(shell echo `tulip-config --cxxflags`) 
QMAKE_CXXFLAGS += -std=c++14
#QMAKE_CXXFLAGS += -DDEBUG_ONLY_PROCESSED_NODES
#QMAKE_CXXFLAGS += -DDEBUG_MISSING_PATHS
#QMAKE_CXXFLAGS += -DDEBUG_VELO
QMAKE_CXXFLAGS += -DNDEBUG
LIBS += \$(shell echo `tulip-config --libs`)
CONFIG += console

# install
target.path = .
INSTALLS += target
