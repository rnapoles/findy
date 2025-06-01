#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>

class AppConfig : public QObject
{
    Q_OBJECT
public:

    static AppConfig *instance()
    {
        if (!s_instance)
            s_instance = new AppConfig;
        return s_instance;
    }

    void setDirIndex(QString p_DirIndex);
    void setSourceDocAvailable(bool p_IsSourceDocAvailable);


	
signals:
    void configchange();
public slots:


    QString getDirIndex();
    bool IsSourceDocAvailable();

private:

    explicit AppConfig(QObject *parent = 0);

    static AppConfig *s_instance;

    QString p_DirIndex;
    bool p_IsSourceDocAvailable;
};

#endif // APPCONFIG_H
