#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T08:59:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OmaPuoli
TEMPLATE = lib
CONFIG += c++11
CONFIG += staticlib

# Lisätty kurssin puolen tavaroiden käyttämiseksi
INCLUDEPATH += $$PWD/../KurssinPuoli
DEPENDPATH += $$PWD/../KurssinPuoli
#LIBS += $$PWD/../KurssinPuoli/sijainti.o


SOURCES += \
    pelinakyma.cpp \
    luopeli.cc \
    kaupunki.cc \
    tilasto.cpp \
    drone.cc \
    lopetusikkuna.cpp

HEADERS  += \
    pelinakyma.hh \
    kaupunki.hh \
    tilasto.hh \
    drone.hh \
    lopetusikkuna.hh
FORMS += \
    pelinakyma.ui \
    lopetusikkuna.ui
