# python library
TARGET = $$PWD/poke.so
# put the .o files in separate folder to keep it clean
OBJECTS_DIR = obj

cache()
CONFIG += console c++14
CONFIG -= app_bundle

SOURCES += \
    pyBindings.cpp

SOURCES += $$files(../GameCore/src/*.cpp)
SOURCES -= ../GameCore/src/main.cpp

INCLUDEPATH += ../GameCore/include
INCLUDEPATH += ../pybind11/include


QMAKE_LFLAGS += -shared
QMAKE_CXXFLAGS+=$$system(python-config --cflags)
QMAKE_LFLAGS+=$$system(python-config --ldflags)

# Python redefines some qt keywords
CONFIG += no_keywords

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
<<<<<<< HEAD

=======
>>>>>>> 2f11f9b8d99db7eb9a468b1dde88e65e471c9c89
