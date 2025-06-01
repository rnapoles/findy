#include "magicfileinfo.h"
#include <libs/magic/magic.h>
#include <QFile>
/*

    MagicFileInfo f("test.pdf");

    if(!f.Error){
        qDebug() << f.Charset;
        qDebug() << f.MimeType;
        qDebug() << f.Description;
    } else {
        qDebug() << f.ErrorStr;
    }

*/

MagicFileInfo::MagicFileInfo(const QString &filename)
{

    this->charset.clear();
    this->mimeType.clear();
    this->description.clear();
    this->errorStr.clear();
    this->error = false;

    if(QFile::exists(filename)){

        char *actual_file = (char *) filename.toLatin1().constData();
        const char *magic_full;
        magic_t magic_cookie;

        magic_cookie = magic_open(MAGIC_MIME); //Only charset

        if (magic_cookie == NULL) {
            this->error = true;
            this->errorStr = QString("No se pudo inicializar libmagic");
            return ;
        }

        if (magic_load(magic_cookie,"magic.mgc") != 0) {
            this->error = true;
            this->errorStr = QString("No se pudo cargar magic.mgc");
            magic_close(magic_cookie);
            return ;
        }




        magic_full = magic_file(magic_cookie, actual_file);

        magic_setflags(magic_cookie,MAGIC_MIME_TYPE);
        magic_full = magic_file(magic_cookie, actual_file);
        this->mimeType = QString(magic_full);

        magic_setflags(magic_cookie,MAGIC_NONE);
        magic_full = magic_file(magic_cookie, actual_file);
        this->description = QString(magic_full);

        magic_setflags(magic_cookie,MAGIC_MIME_ENCODING);
        magic_full = magic_file(magic_cookie, actual_file);
        this->charset = QString(magic_full);

        //delete [] magic_full;

        magic_close(magic_cookie);

    } else {
        this->error = true;
        this->errorStr = QString("El fichero %1 no existe.").arg(filename);
    }
}
