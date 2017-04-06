#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:20:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PFA
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14

INCLUDEPATH += /home/raptapia/Documents/logiciels/tulip-4.10.0/install-debug/include/ \
    ../../sgbd/include/ \
    ../../controller/ \
    /home/raptapia/Documents/logiciels/wrappy/include/

SOURCES += main.cpp\
    mainwindow.cpp \
    periodfilter.cpp \
    usersfilter.cpp \
    tripsfilter.cpp \
    heatmapsurvey.cpp \
    densityfilter.cpp \
    ../../controller/*.cpp \
    ../../import/*.cpp

HEADERS  += mainwindow.hpp \
    periodfilter.hpp \
    usersfilter.hpp \
    tripsfilter.hpp \
    heatmapsurvey.hpp \
    densityfilter.hpp \
    ../../controller/*.hpp \
    ../../import/*.hpp

LIBS +=  `tulip-config-debug --libs` \
	-L../sgbd/lib -lgraphdb \
	-L/home/raptapia/Documents/logiciels/wrappy/build/ -lwrappy

