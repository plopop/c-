TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    hierarchical_mutex.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    hierarchial_mutex.h

