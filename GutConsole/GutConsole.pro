#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T10:00:02
#
#-------------------------------------------------

QT       += core xml
QT       -= gui

TARGET = gut
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

VERSION = 1.0.1
DEFINES += EXEVERSION=\\\"$$VERSION\\\" # Makes verion available to c++


SOURCES += main.cpp \
    gutengine.cpp

HEADERS += \
    gutengine.h

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
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10 #2 Yosemite

    # GDAL is required
    GDALNIX = /Library/Frameworks/GDAL.framework/Versions/1.11/unix
    LIBS += -L$$GDALNIX/lib -lgdal
    INCLUDEPATH += $$GDALNIX/include
    DEPENDPATH  += $$GDALNIX/include

    # Compile to a central location
    DESTDIR = $$OUT_PWD/../../../Deploy/$$BUILD_TYPE
}
unix:!macx {
    message("Unix")
    # Compile to a central location
    DESTDIR = $$OUT_PWD/../../../Deploy/$$BUILD_TYPE

    target.path = /usr/bin
    INSTALLS += target

    # GDAL is required
    LIBS += -L/usr/local/lib -lgdal
    INCLUDEPATH += /usr/include/gdal
    DEPENDPATH  += /usr/include/gdal

}

# Tell it where to find compiled RasterManager.dll
INCLUDEPATH += $$PWD/../GutCore
DEPENDPATH += $$PWD/../GutCore
INCLUDEPATH += $$PWD/../../../RasterManager/rastermanager/RasterManager
DEPENDPATH += $$PWD/../../../RasterManager/rastermanager/RasterManager
LIBS += -L$$DESTDIR -lRasterManager
#LIBS += -L$$DESTDIR -lRaster2PNG
LIBS += -L$$DESTDIR -lGutCore
message("Building to: $$DESTDIR")
message("Libs: $$LIBS")


