# exe name
TARGET=PokemonTCG
# put the .o files in separate folder to keep it clean
OBJECTS_DIR=obj

cache()
CONFIG += console c++14
CONFIG -= app_bundle

SOURCES += $$files(../GameCore/src/*.cpp)

HEADERS += $$files(../GameCore/include/*.h)

INCLUDEPATH+=$$PWD/include
INCLUDEPATH+=../pybind11/include

linux {
    LIBS += -L /usr/local/lib/python2.7 -lpython2.7
    INCLUDEPATH += /usr/include/python2.7
    DEPENDPATH += /usr/include/python2.7
}
