#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>

class FileInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString MimeType READ MimeType WRITE setMimeType)
    Q_PROPERTY(QString Command READ Command WRITE setCommand)
    Q_PROPERTY(QString Extension READ Extension WRITE setExtension)
public:
    explicit FileInfo(QObject *parent = 0);
    FileInfo(const FileInfo &f);
    FileInfo &operator=(const FileInfo &f);

    QString MimeType() const;
    void setMimeType(const QString& mimeType);

    QString Command() const;
    void setCommand(const QString& command);

    QString Extension() const;
    void setExtension(const QString& extension);

private:
    QString p_MimeType;
    QString p_Command;
    QString p_Extension;
};

#endif // FILEINFO_H
