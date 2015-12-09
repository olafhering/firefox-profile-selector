HEADERS       = ffps.h
SOURCES       = ffps.cpp \
                main.cpp

QT += core
QT += gui
QT += widgets
QMAKE_CFLAGS += $(EXTRA_CFLAGS)
QMAKE_CXXFLAGS += $(EXTRA_CXXFLAGS)
TEMPLATE = app
target.path += /usr/bin
INSTALLS += target
