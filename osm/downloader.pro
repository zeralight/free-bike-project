TEMPLATE = app

SOURCES = downloader.cpp Downloader.cpp

QMAKE_CXXFLAGS += -std=c++14

QT += core
QT -= gui 
QT += network

CONFIG   += console
CONFIG   -= app_bundle
