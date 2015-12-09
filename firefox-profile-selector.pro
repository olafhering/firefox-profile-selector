HEADERS       = ffps.h
SOURCES       = ffps.cpp \
                main.cpp

TEMPLATE = app
target.path += $$[QT_INSTALL_BINS]/
INSTALLS += target
