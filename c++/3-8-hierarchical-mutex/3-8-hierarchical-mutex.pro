TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += -pthread

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    hierarchial_mutex.h


#QMAKE_CXXFLAGS += -pthread
