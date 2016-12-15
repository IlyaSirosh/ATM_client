QT += core gui
QT += network


CONFIG += c++11



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATM_client
CONFIG += console

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp \
    atm2.cpp \
    keypad.cpp \
    cardeater.cpp \
    controller.cpp \
    atmstate.cpp \
    cashteller.cpp

HEADERS += \
    client.h \
    atm2.h \
    keypad.h \
    cardeater.h \
    controller.h \
    atmstate.h \
    cashteller.h

FORMS += \
    atm.ui
