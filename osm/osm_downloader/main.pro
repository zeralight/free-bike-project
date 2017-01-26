QT       += core
QT       -= gui
 
QMAKE_CXXFLAGS += -std=c++14
TARGET = Downloader 
CONFIG   += console
CONFIG   -= app_bundle
QT += network
TEMPLATE = app
 
SOURCES += main.cpp
