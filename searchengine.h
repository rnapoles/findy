#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QObject>
#include <clucenehelper.h>

class SearchEngine : public QObject
{
    Q_OBJECT
public:

    void index();
    void stop();

    void search(const QString &str);
    void textCompletion(const QString &str);

    void useMultiFieldSearch(bool b);
    void setSearchField (const QString Field);

    static SearchEngine *instance();
    ~SearchEngine();

private:
    explicit SearchEngine(QObject *parent = 0);
    void setupEngine();
    bool isAvailable();


    static SearchEngine *s_instance;
    CLuceneHelper *engine;

signals:
    void searchStarted();
    void searchFinished(int size);
    void onTextCompletionReady(const QList<IndexedDocument>& results,double time);
    void onSearchReady(const QList<IndexedDocument>& results,double tiempo);
    void onError(const int ErrType,const QString Msg,const QString OrgMsg);


private slots:
    void slotSearchFinish(const QList<IndexedDocument>& results,double tiempo);
    void slotTextCompletionFinish(const QList<IndexedDocument>& results,double tiempo);
    void slotOnError(const int ErrType,const QString Msg,const QString OrgMsg);

    
};

#endif // SEARCHENGINE_H
