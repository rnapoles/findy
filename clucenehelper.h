#ifndef CLUCENEHELPER_H
#define CLUCENEHELPER_H

#include <QObject>
#include <QList>
#include <QStringList>

#include <CLucene/CLucene.h>
#include <CLucene/StdHeader.h>
#include <CLucene/util/Misc.h>
#include <CLucene/snowball/SnowballAnalyzer.h>
#include <lucenedocument.h>
#include <magicfileinfo.h>

using namespace lucene::index;
using namespace lucene::analysis;
using namespace lucene::util;
using namespace lucene::queryParser;
using namespace lucene::store;
using namespace lucene::document;
using namespace lucene::search;

//#define ErrBd 1
//#define ErrLucene 2


class CLuceneHelper : public QObject
{
    Q_OBJECT
public:
    static CLuceneHelper *instance()
    {
        if (!s_instance)
          s_instance = new CLuceneHelper;
        return s_instance;
    }

    ~CLuceneHelper();

    void search(const QString &cad,size_t limite=0);
    bool isAvailable();
    QString cleanHtml(const QString &cad) const;
    QString toError(const int) const;
    QStringList getFieldNames() ;
    QString lastQuery() const;

//    void useMultiFieldSearch(void);
//    void setSearchField(const QString Field);

    void setIndexDirectory(const QString &Dir);

    QString getDirIndex() const;

    void index(const QString &path);
    void optimize();

private:

    static CLuceneHelper *s_instance;
    QString dirIndex;

    //snowball::SnowballAnalyzer an;
    lucene::analysis::WhitespaceAnalyzer an;
    //lucene::analysis::standard::StandardAnalyzer an;
    IndexWriter *writer ;

    QString LastQueryString;
    explicit CLuceneHelper(QObject *parent = 0);

    MagicFileInfo GetMagicfileinfo(const QString &FileName);

signals:
    void onSearchFinish(const QList<IndexedDocument>& results,double tiempo);
    void indexContentStarted(int max);
    void indexContentProgress(int progress);
    void indexContentFinished();
    void onError(const int ErrType,const QString Msg,const QString OrgMsg);

public slots:

};

#endif // CLUCENEHELPER_H
