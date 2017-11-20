cache()
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
    src/main.cpp \
    src/game.cpp

HEADERS += \
    include/card.h \
    include/pokemoncard.h \
    include/game.h \
    include/pokemonenums.h

INCLUDEPATH+=$$PWD/include
INCLUDEPATH+=../pybind11/include

LIBS += -L /usr/local/lib/python2.7 -lpython2.7

INCLUDEPATH += /usr/include/python2.7
DEPENDPATH += /usr/include/python2.7

QMAKE_CXXFLAGS += -std=c++1z
