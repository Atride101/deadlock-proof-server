#-------------------------------------------------
#
# Project created by QtCreator 2014-02-20T03:22:40
#
#-------------------------------------------------

QT       += gui core network

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}


TARGET = TP2Client
CONFIG   += console

TEMPLATE = app


SOURCES += main.cpp \
    clientthread.cpp

HEADERS += \
    clientthread.h
