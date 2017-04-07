#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:20:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PFA
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14 \
-DNDEBUG

INCLUDEPATH += /home/leo/Logiciels/tulip-4.10.0/install-release/include/ \
    ../../sgbd/include/ \
    ../../controller/ \
    /home/leo/Logiciels/wrappy/include/

SOURCES += main.cpp\
    mainwindow.cpp \
    periodfilter.cpp \
    usersfilter.cpp \
    tripsfilter.cpp \
    heatmapsurvey.cpp \
    densityfilter.cpp \
    ../../controller/*.cpp \
    ../../import/cityDB.cpp

HEADERS  += mainwindow.hpp \
    periodfilter.hpp \
    usersfilter.hpp \
    tripsfilter.hpp \
    heatmapsurvey.hpp \
    densityfilter.hpp \
    ../../controller/*.hpp \
    ../../import/cityDB.hpp

LIBS +=  `tulip-config --libs` \
	-L../../sgbd/lib -lgraphdb \
	-L/home/leo/Logiciels/wrappy/build/ -lwrappy
