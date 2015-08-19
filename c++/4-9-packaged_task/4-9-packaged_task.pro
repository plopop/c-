TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11 thread

#QMAKE_CXXFLAGS += -pthread -std=c++11



SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

