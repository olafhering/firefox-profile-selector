HEADERS       = ffps.h
SOURCES       = ffps.cpp \
                main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/ffps
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS ffps.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/widgets/ffps
INSTALLS += target sources
