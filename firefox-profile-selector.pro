HEADERS       = ffps.h
SOURCES       = ffps.cpp \
                main.cpp

QMAKE_CFLAGS += $(EXTRA_CFLAGS)
QMAKE_CXXFLAGS += $(EXTRA_CXXFLAGS)
TEMPLATE = app
target.path += /usr/bin
INSTALLS += target
