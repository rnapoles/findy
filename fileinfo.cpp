#include "fileinfo.h"

FileInfo::FileInfo(QObject *parent) : QObject(parent)
{
}

FileInfo::FileInfo(const FileInfo & f)
{
    this->p_MimeType = f.p_MimeType;
    this->p_Command = f.p_Command;
    this->p_Extension = f.p_Extension;
}

FileInfo &FileInfo::operator=(const FileInfo &f)
{

    if(this == &f) return *this;

    this->p_MimeType = f.p_MimeType;
    this->p_Command = f.p_Command;
    this->p_Extension = f.p_Extension;

    return *this;
}

QString FileInfo::MimeType() const
{
    return this->p_MimeType;
}

void FileInfo::setMimeType(const QString &mimeType)
{
    this->p_MimeType = mimeType;
}

QString FileInfo::Command() const
{
    return this->p_Command;
}

void FileInfo::setCommand(const QString &command)
{
    this->p_Command = command;
}

QString FileInfo::Extension() const
{
    return this->p_Extension;
}

void FileInfo::setExtension(const QString &extension)
{
    this->p_Extension = extension;
}
