#ifndef MAGICFILEINFO_H
#define MAGICFILEINFO_H
#include <QString>

class MagicFileInfo
{
public:
    MagicFileInfo(const QString &filename);
    QString mimeType;
    QString charset;
    QString description;
    QString errorStr;
    bool error;
};

#endif // MAGICFILEINFO_H
