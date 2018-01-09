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

win32 {
    LIBS+= "C:/Python27/libs/python27.lib"
    INCLUDEPATH += C:/Python27/include
    DEPENDPATH += C:/Python27/include
}


