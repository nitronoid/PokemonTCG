# python library
TARGET = $$PWD/poke.so
# put the .o files in separate folder to keep it clean
OBJECTS_DIR = obj

cache()
CONFIG += console c++14
CONFIG -= app_bundle

SOURCES += \
    pyBindings.cpp

SOURCES += $$files(../GameCore/src/*.cpp, true)
SOURCES -= ../GameCore/src/main.cpp

INCLUDEPATH += ../GameCore/include
INCLUDEPATH += ../pybind11/include


QMAKE_LFLAGS += -shared
QMAKE_CXXFLAGS+=$$system(python-config --cflags)
QMAKE_LFLAGS+=$$system(python-config --ldflags)

# Python redefines some qt keywords
CONFIG += no_keywords
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
