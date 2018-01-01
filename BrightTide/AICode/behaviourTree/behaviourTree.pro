TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    compositenode.cpp \
    selector.cpp \
    sequence.cpp \
    testaction.cpp \
    condition.cpp \
    conditionenergy.cpp \
    conditiondead.cpp \
    conditionsecondattack.cpp \
    cards.cpp \
    conditionlistempty.cpp

HEADERS += \
    node.h \
    compositenode.h \
    selector.h \
    sequence.h \
    testaction.h \
    condition.h \
    conditionenergy.h \
    conditiondead.h \
    conditionsecondattack.h \
    cards.h \
    conditionlistempty.h

