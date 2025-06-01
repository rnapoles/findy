#ifndef FILEINFOLIST_H
#define FILEINFOLIST_H

#include <QObject>
#include <QList>
#include <QMetaType>
#include "fileinfo.h"

//typedef QList<FileInfo> ListFileInfo;


class FileInfoList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<FileInfo> FileList READ FileList WRITE setFileList)

public:
    explicit FileInfoList(QObject *parent = 0);
    FileInfoList(const FileInfoList &f);
    FileInfoList &operator=(const FileInfoList &f);

    QList<FileInfo> FileList() const;
    void setFileList(const QList<FileInfo> &FileList);
    void Append(const FileInfo &File);
private:
   QList<FileInfo> p_FileList;

    
};

Q_DECLARE_METATYPE(QList<FileInfo>)
Q_DECLARE_METATYPE(FileInfo)
Q_DECLARE_METATYPE(FileInfoList)

QDataStream &operator>>(QDataStream &in, QList<FileInfo> &list);
QDataStream &operator<<(QDataStream &out, const QList<FileInfo> &list);

QDataStream &operator>>(QDataStream &in, FileInfo &fi);
QDataStream &operator<<(QDataStream &out,FileInfo &fi);

QDataStream &operator>>(QDataStream &in, FileInfoList &fi);
QDataStream &operator<<(QDataStream &out,FileInfoList &fi);

int registerListFileInfoMetaTypes();

#endif // FILEINFOLIST_H
