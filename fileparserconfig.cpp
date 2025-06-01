#include "fileparserconfig.h"
#include <magicfileinfo.h>
#include <QSettings>
#include <QStringList>
#include <QDebug>


FileParserConfig *FileParserConfig::s_instance = 0;

FileParserConfig::FileParserConfig()
{
    this->fileParserList.clear();
    this->loadConfig();
}

FileParserConfig *FileParserConfig::instance()
{
    if (!s_instance)
        s_instance = new FileParserConfig;
    return s_instance;
}

void FileParserConfig::loadConfig()
{


    QString configFileName= "FileParser.ini";
    QSettings settings(configFileName,QSettings::IniFormat);
    QStringList groups = settings.childGroups();
    //qDebug() << groups;

    int size = groups.size();

    for (int i = 0; i < size ; ++i){
        FileParser fp;
        settings.beginGroup(groups.at(i));
        fp.name = groups.at(i);
        fp.command = settings.value("Command","").toString();
        fp.mimeType = settings.value("MimeType","").toString();
        fp.extensions = settings.value("Extensions","").toStringList();
        settings.endGroup();
        fileParserList.append(fp);
    }

}

void FileParserConfig::writeConfig()
{
    QString configFileName= "FileParser.ini";
    QSettings settings(configFileName,QSettings::IniFormat);

    int size = fileParserList.size();

    for (int i = 0; i < size ; ++i){
        FileParser fp;
        settings.beginGroup(fileParserList.at(i).name);
        settings.setValue("Command",fp.command);
        settings.setValue("MimeType",fp.mimeType);
        settings.setValue("Extensions",fp.extensions);
        settings.endGroup();
    }
    settings.sync();

}
