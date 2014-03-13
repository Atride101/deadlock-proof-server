#-------------------------------------------------
#
# Project created by QtCreator 2014-02-19T23:29:13
#
#-------------------------------------------------

QT += gui core network

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

TARGET = TP2Server
TEMPLATE = app


SOURCES += main.cpp\
        graphicInterface.cpp \
    resourceMeter.cpp \
    server.cpp

HEADERS  += graphicInterface.h \
    resourceMeter.h \
    server.h

FORMS    += graphicInterface.ui
