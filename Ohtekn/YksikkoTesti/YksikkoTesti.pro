#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T09:01:10
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_yksikkotesti
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += C++11

TEMPLATE = app
INCLUDEPATH += $$PWD/../OmaPuoli
DEPENDPATH += $$PWD/../OmaPuoli
INCLUDEPATH += $$PWD/../KurssinPuoli
DEPENDPATH += $$PWD/../KurssinPuoli


SOURCES += tst_yksikkotesti.cc \
           ../OmaPuoli/tilasto.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
