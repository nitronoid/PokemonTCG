# exe name
TARGET=PokemonTCG
# put the .o files in separate folder to keep it clean
OBJECTS_DIR=obj

cache()
CONFIG += console c++14
CONFIG -= app_bundle

SOURCES += $$files(../GameCore/src/*.cpp) \

<<<<<<< HEAD
HEADERS += $$files(../GameCore/include/*.h) \
    include/effect.h \
=======
HEADERS += $$files(../GameCore/include/*.h)
>>>>>>> bd62c71ab00aef110715541c1d70e1451d46b0f4

INCLUDEPATH+=$$PWD/include
INCLUDEPATH+=../pybind11/include
INCLUDEPATH+=../behaviourTree

linux {
    LIBS += -L /usr/local/lib/python2.7 -lpython2.7
    INCLUDEPATH += /usr/include/python2.7
    DEPENDPATH += /usr/include/python2.7
}
