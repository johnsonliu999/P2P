QT += core
QT -= gui

QT += network

CONFIG += c++11

TARGET = Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    processthread.cpp

HEADERS += \
    server.h \
    processthread.h
