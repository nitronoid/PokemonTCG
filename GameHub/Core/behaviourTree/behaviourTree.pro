TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    compositenode.cpp \
    sequence.cpp \
    selector.cpp \
    condition.cpp \
    action.cpp

HEADERS += \
    node.h \
    compositenode.h \
    sequence.h \
    selector.h \
    condition.h \
    action.h
