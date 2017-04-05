#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:20:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PFA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    periodfilter.cpp \
    usersfilter.cpp \
    tripsfilter.cpp \
    heatmapsurvey.cpp \
    densityfilter.cpp

HEADERS  += mainwindow.hpp \
    periodfilter.hpp \
    usersfilter.hpp \
    tripsfilter.hpp \
    heatmapsurvey.hpp \
    densityfilter.hpp
