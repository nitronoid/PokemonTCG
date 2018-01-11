cache()
CONFIG += console c++14
CONFIG -= app_bundle

SOURCES += \
    pyBindings.cpp

SOURCES += $$files(../GameCore/src/*.cpp)
SOURCES -= ../GameCore/src/main.cpp

INCLUDEPATH+=../GameCore/include
INCLUDEPATH+=../pybind11/include

TARGET = $$PWD/poke.so

QMAKE_LFLAGS += -shared
QMAKE_CXXFLAGS+=$$system(python-config --cflags)
QMAKE_LFLAGS+=$$system(python-config --ldflags)

CONFIG += no_keywords # Python redefines some qt keywords

linux {
    LIBS += -L /usr/local/lib/python2.7 -lpython2.7
    INCLUDEPATH += /usr/include/python2.7
    DEPENDPATH += /usr/include/python2.7
}
