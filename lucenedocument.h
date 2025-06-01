#ifndef LUCENEDOCUMENT_H
#define LUCENEDOCUMENT_H
#include <QString>

class IndexedDocument
{
public:
    IndexedDocument();
    QString path;
    QString fileName;
    QString extension;
    QString mimeType;
    QString category;
    QString content;
};

#endif // LUCENEDOCUMENT_H
