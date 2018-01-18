# exe name
TARGET = PokemonTCG
# put the .o files in separate folder to keep it clean
OBJECTS_DIR = obj

cache()
CONFIG += console c++14
CONFIG -= app_bundle

# Core
HEADERS += $$files(../GameCore/include/*.h, true)
SOURCES += $$files(../GameCore/src/*.cpp, true)

# Roaring Heat AI
HEADERS += $$files(../../../RoaringHeat/include/*.h, true)
SOURCES += $$files(../../../RoaringHeat/src/*.cpp, true)
INCLUDEPATH += ../../../RoaringHeat/include

# Bright Tide AI
HEADERS += $$files(../../../BrightTide/include/*.h, true)
SOURCES += $$files(../../../BrightTide/src/*.cpp, true)
INCLUDEPATH += ../../../BrightTide/include

INCLUDEPATH += $$PWD/include
INCLUDEPATH += ../pybind11/include
# Reasons why this is neccessary explained on the pybind faq
# github.com/pybind/pybind11/blob/master/docs/faq.rst#someclass-declared-with-greater-visibility-than-the-type-of-its-field-someclassmember--wattributes
QMAKE_CXXFLAGS += -fvisibility=hidden

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
