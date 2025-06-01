#include "fileinfolist.h"
#include <QDebug>

FileInfoList::FileInfoList(QObject *parent) :
    QObject(parent)
{
}

FileInfoList::FileInfoList(const FileInfoList & f)
{
    this->p_FileList = f.p_FileList;

}

FileInfoList &FileInfoList::operator=(const FileInfoList &f)
{

    if(this == &f) return *this;

    this->p_FileList = f.p_FileList;


    return *this;
}

QList<FileInfo> FileInfoList::FileList() const
{
    return this->p_FileList;
}

void FileInfoList::setFileList(const QList<FileInfo> &FileList)
{
    this->p_FileList = FileList;
}

void FileInfoList::Append(const FileInfo &File)
{
    this->p_FileList.append(File);
}


QDataStream &operator<<(QDataStream &out, const QList<FileInfo> &list){

    qDebug()<< "QDataStream &operator<<";
    int size = list.size();
    for (int i = 0; i < size; ++i) {
        out << list.at(i).MimeType()
            << list.at(i).Command()
            << list.at(i).Extension();
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, QList<FileInfo> &list){

    qDebug()<< "QDataStream &operator>>";

    QString MimeType;
    QString Command;
    QString Extension;

    in >> MimeType >> Command >> Extension;

    return in;
}

/*
QDataStream &operator>>(QDataStream &in, ListFileInfo &list)
{
    return operator>>(in, static_cast<QList<FileInfo> &>(list));
}

QDataStream &operator<<(QDataStream &out, const ListFileInfo &list)
{
    return operator<<(out, static_cast<const QList<FileInfo> &>(list));
}
*/

QDataStream &operator>>(QDataStream &in, FileInfo &fi){
    qDebug()<< "QDataStream &operator>>";

    QString MimeType;
    QString Command;
    QString Extension;

    in >> MimeType >> Command >> Extension;

    fi.setMimeType(MimeType);
    fi.setCommand(Command);
    fi.setExtension(Extension);

    return in;
}

QDataStream &operator<<(QDataStream &out,FileInfo &fi){
    qDebug()<< "QDataStream &operator<<";
    out << fi.MimeType() << fi.Command() << fi.Extension();
    return out;
}

QDataStream &operator>>(QDataStream &in, FileInfoList &fi){
    qDebug()<< "QDataStream &operator>>";

    QList<FileInfo> f;
    in >> f;
    fi.setFileList(f);

    return in;
}

QDataStream &operator<<(QDataStream &out,FileInfoList &fi){
    qDebug()<< "QDataStream &operator<<";

    out << fi.FileList();
    return out;
}


int registerListFileInfoMetaTypes()
{

    qRegisterMetaType< QList<FileInfo> >("QList<FileInfo>");
    qRegisterMetaTypeStreamOperators< QList<FileInfo> >("QList<FileInfo>");

    qRegisterMetaType<FileInfo>("FileInfo");
    //qRegisterMetaTypeStreamOperators<FileInfo>("FileInfo");

    qRegisterMetaType<FileInfoList>("FileInfoList");
    //qRegisterMetaTypeStreamOperators<FileInfoList>("FileInfoList");

    return 0; // something
}
