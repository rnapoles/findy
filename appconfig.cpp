#include "appconfig.h"

AppConfig *AppConfig::s_instance = 0;

AppConfig::AppConfig(QObject *parent):QObject(parent)
{
    this->p_DirIndex = "";
    this->p_IsSourceDocAvailable = false;
}

void AppConfig::setDirIndex(QString p_DirIndex) {
    this->p_DirIndex = p_DirIndex;
    emit configchange();
}

QString AppConfig::getDirIndex() {
    return this->p_DirIndex;
}

void AppConfig::setSourceDocAvailable(bool p_IsSourceDocAvailable) {
    this->p_IsSourceDocAvailable = p_IsSourceDocAvailable;
    emit configchange();
}

bool AppConfig::IsSourceDocAvailable() {
    return this->p_IsSourceDocAvailable;
}

