QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = ATM_client
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp

HEADERS += \
    client.h
