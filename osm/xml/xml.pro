SOURCES += main.cpp OsmParser.cpp InternalNode.cpp 
QT -= gui
QMAKE_CXXFLAGS += -std=c++14

CONFIG += console

# install
target.path = .
INSTALLS += target
