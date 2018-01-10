cache()
CONFIG += console c++14
CONFIG -= app_bundle

SOURCES += $$files(../GameHub/Core/GameCore/src/*.cpp)
SOURCES += \
    RoaringFluke.cpp

HEADERS += $$files(../GameHub/Core/GameCore/include/*.h) 
HEADERS += \
    RoaringFluke.h

INCLUDEPATH+=$$PWD/include
INCLUDEPATH+=../GameHub/Core/GameCore/include
INCLUDEPATH+=../GameHub/Core/pybind11/include

linux {
    LIBS += -L /usr/local/lib/python2.7 -lpython2.7
    INCLUDEPATH += /usr/include/python2.7
    DEPENDPATH += /usr/include/python2.7
}
