# exe name
TARGET = PokemonTCG
# put the .o files in separate folder to keep it clean
OBJECTS_DIR = obj

cache()
CONFIG += console c++14
CONFIG -= app_bundle

# Core
HEADERS += $$files(../GameCore/include/*.h)
SOURCES += $$files(../GameCore/src/*.cpp)

# Roaring Heat AI
HEADERS += $$files(../../../RoaringHeat/include/*.h)
SOURCES += $$files(../../../RoaringHeat/src/*.cpp)
INCLUDEPATH += ../../../RoaringHeat/include

INCLUDEPATH += $$PWD/include
INCLUDEPATH += ../pybind11/include

linux: {
    LIBS += -L /usr/local/lib/python2.7 -lpython2.7
    INCLUDEPATH += /usr/include/python2.7
    DEPENDPATH += /usr/include/python2.7
}
macx: {
    LIBS += -L /usr/bin/python2.7 -lpython2.7
    INCLUDEPATH += /Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
    DEPENDPATH += /Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
}
