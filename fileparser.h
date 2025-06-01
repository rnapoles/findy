#ifndef FILEPARSER_H
#define FILEPARSER_H
#include <QStringList>

class FileParser
{
public:
    FileParser();
    QString name;
    QString mimeType;
    QString command;
    QStringList extensions;
};

#endif // FILEPARSER_H
