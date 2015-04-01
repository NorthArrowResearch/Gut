#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T10:00:46
#
#-------------------------------------------------

QT       += xml core
QT       -= gui

TARGET = GutCore
TARGET_EXT = .dll # prevent version suffix on dll
TEMPLATE = lib

VERSION = 1.0.2
DEFINES += GUTLIBVERSION=\\\"$$VERSION\\\" # Makes verion available to c++
DEFINES += GDALMAJ=\\\"1\\\" # Minimum Major Version of GDAL we need
DEFINES += GDALMIN=\\\"11\\\" # Minimum Minor Version of GDAL we need
DEFINES += MINRASTERMAN=\\\"6.1.6\\\" # Minimum Version of GDAL we need

DEFINES += GUT_LIBRARY

SOURCES += \
    unit.cpp \
    xmlfile.cpp \
    gut_raster.cpp \
    gut_run.cpp \
    gut_interface.cpp \
    unit_hsuplfan.cpp \
    rmoperation.cpp

HEADERS +=\
        gut_global.h \
    gut_exception.h \
    unit.h \
    xmlfile.h \
    gut_raster.h \
    gut_run.h \
    gut_interface.h \
    unit_hsuplfan.h \
    rmoperation.h

CONFIG(release, debug|release): BUILD_TYPE = release
else:CONFIG(debug, debug|release): BUILD_TYPE = debug

win32 {
    ## There's some trickiness in windows 32 vs 64-bits
    !contains(QMAKE_TARGET.arch, x86_64) {
        ARCH = "32"
        message("x86 build (32 bit) ")
    } else {
        message("x86_64 build (64 bit) ")
        ARCH = "64"
    }

    # GDAL is required
    GDALWIN = $$PWD/../Libraries/gdalwin$$ARCH-1.10.1
    LIBS += -L$$GDALWIN/lib/ -lgdal_i
    INCLUDEPATH += $$GDALWIN/include
    DEPENDPATH += $$GDALWIN/include

    # Compile to a central location
    DESTDIR = $$OUT_PWD/../../../Deploy/$$BUILD_TYPE$$ARCH
}
macx{
    ## OSX common build here
    message("Mac OSX x86_64 build (64bit)")
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10

    # Compile to a central location
    DESTDIR = $$OUT_PWD/../../../Deploy/$$BUILD_TYPE

    # GDAL is required
    # GDALNIX = /Users/matt/Projects/nar/gdal/gdal-1.11-debug
    GDALNIX = /Library/Frameworks/GDAL.framework/Versions/1.11/unix
    # SOURCES += /Users/matt/Projects/nar/Libraries/gdal/gdal/alg/gdalproximity.cpp
    LIBS += -L$$GDALNIX/lib -lgdal
    INCLUDEPATH += $$GDALNIX/include
    DEPENDPATH  += $$GDALNIX/include
}
unix:!macx {
    message("Unix")
    # Compile to a central location
    DESTDIR = $$OUT_PWD/../../../Deploy/$$BUILD_TYPE

    target.path = /usr/lib
    INSTALLS += target

    # GDAL is required
    LIBS += -L/usr/local/lib -lgdal
    INCLUDEPATH += /usr/include/gdal
    DEPENDPATH  += /usr/include/gdal
}

INCLUDEPATH += $$PWD/../../../RasterManager/rastermanager/RasterManager
DEPENDPATH += $$PWD/../../../RasterManager/rastermanager/RasterManager
LIBS += -L$$DESTDIR -lRasterManager

message("Building to: $$DESTDIR")
