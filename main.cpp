//#include <QtGui/QApplication>

#include "libs/qtsingleapplication/qtsingleapplication.h"
#include <BreakpadHandler.h>
#include <error/reporter.h>

#include <QPlastiqueStyle>
#include <QLocale>
#include <QDir>
#include <QDesktopServices>
#include "mainwindow.h"
#include "appconfig.h"

#include <QDebug>
#include <fileparserconfig.h>


int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    QtSingleApplication app(argc, argv);

    if (app.isRunning()) {
        QString msg("show");
        app.sendMessage(msg, 5000);
        return 0;
    }

    QTextCodec *linuxCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(linuxCodec);
    QTextCodec::setCodecForCStrings(linuxCodec);
    QTextCodec::setCodecForLocale(linuxCodec);
    QLocale::setDefault(QLocale(QLocale::Spanish, QLocale::Cuba));


    app.setOrganizationName("Dragons Hunters");
    app.setApplicationName("Sabueso");

    //Manejador de Errores
    QString path = QDir::toNativeSeparators(QDesktopServices::storageLocation(QDesktopServices::DataLocation)+"\\crashes");
    //qDebug()<<path;
    BreakpadQt::GlobalHandler *ErrorHandler = BreakpadQt::GlobalHandler::instance();
    ErrorHandler->setDumpPath(path);
    path = QApplication::applicationDirPath()+QDir::separator()+"ErrorReporter";
    ErrorHandler->setReporter(path);

    QTranslator qtTranslator;
    if(qtTranslator.load("qt_es","locales")){
        qDebug()<<"Locales cargados";
    }
    app.installTranslator(&qtTranslator);

    AppConfig::instance();

    MainWindow w;
    w.show();

    return app.exec();
}
