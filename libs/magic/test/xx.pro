#-------------------------------------------------
#
# Project created by QtCreator 2013-07-02T11:56:44
#
#-------------------------------------------------

QT       += core gui webkit network

TARGET = Sabueso
TEMPLATE = app

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/includes/google-breakpad

     debug {

     }

    release {

    }

 win32 {
  INCLUDEPATH += $$PWD/includes/Windows
  LIBS += -L $$PWD/libs/Windows
  #LIBS +=-lzlib
  #LIBS += -lbz2
  LIBS += -lbreakpad
  LIBS += -lclucene-core.dll -lclucene-shared.dll -lclucene-contribs-lib.dll
    #CONFIG(release){
    #    system(del release/qrc_recursos.cpp)
    #    system(del debug/qrc_recursos.cpp)
    #    system(del release/qrc_recursos.o)
    #    system(del debug/qrc_recursos.o)
    #}


 }

 unix {
  INCLUDEPATH += $$PWD/includes/Unix
  LIBS += -L $$PWD/libs/Unix
  #LIBS += -lz -lbz2
  LIBS += -lbreakpad
  LIBS += -lclucene-core -lclucene-shared -lclucene-contribs-lib
 }

win32:QMAKE_RCC = $$[QT_INSTALL_BINS]\\rcc.exe


SOURCES += main.cpp\
        libs/qtsingleapplication/qtsinglecoreapplication.cpp \
        libs/qtsingleapplication/qtsingleapplication.cpp \
        libs/qtsingleapplication/qtlockedfile_win.cpp \
        libs/qtsingleapplication/qtlockedfile_unix.cpp \
        libs/qtsingleapplication/qtlockedfile.cpp \
        libs/qtsingleapplication/qtlocalpeer.cpp \
        error/reporter.cpp \
        mainwindow.cpp \
    appconfig.cpp \
    clucenehelper.cpp

HEADERS  += mainwindow.h \
    libs/qtsingleapplication/qtsinglecoreapplication.h \
    libs/qtsingleapplication/qtsingleapplication.h \
    libs/qtsingleapplication/QtSingleApplication \
    libs/qtsingleapplication/qtlockedfile.h \
    libs/qtsingleapplication/QtLockedFile \
    libs/qtsingleapplication/qtlocalpeer.h \
    error/reporter.h \
    appconfig.h \
    clucenehelper.h

FORMS    += mainwindow.ui
