#include "searchengine.h"
#include <QtConcurrentRun>

SearchEngine *SearchEngine::s_instance = 0;

SearchEngine::SearchEngine(QObject *parent) :
    QObject(parent)
{
    //MultiFieldSearch = false;
    //SearchField = "";
    this->setupEngine();

}

void SearchEngine::setupEngine()
{
    engine = CLuceneHelper::instance();

    //connect(Engine,SIGNAL(indexContentStarted(int)),this,SLOT(indexContentStarted(int)));
    //connect(Engine,SIGNAL(indexContentFinished()),this,SLOT(indexContentFinished()));
    connect(engine,SIGNAL(OnSearchFinish(QList<IndexedDocument>,double)),this,SLOT(slotTextCompletionFinish(QList<IndexedDocument>,double)));
    connect(engine,SIGNAL(OnSearchFinish(QList<IndexedDocument>,double)),this,SLOT(slotSearchFinish(QList<IndexedDocument>,double)));
    connect(engine,SIGNAL(onError(int,QString,QString)),this,SLOT(slotOnError(int,QString,QString)));

}

bool SearchEngine::isAvailable()
{
    return engine->isAvailable();
}


void SearchEngine::index()
{
    //ReadDir("D:\\Qt\\4.7.0\\qt\\src\\corelib");
    engine->setIndexDirectory("");
    engine->index("D:\\Qt\\2010.05\\qt\\src\\corelib\\");
    engine->optimize();
    qDebug()<<"ok";
}

void SearchEngine::stop()
{
}

void SearchEngine::search(const QString &str)
{
    emit searchStarted();

    if(engine->isAvailable()){
        QtConcurrent::run(engine,&CLuceneHelper::search,str,0);
    }
    else {
        QList<IndexedDocument> results;
        emit searchFinished(0);
        emit onSearchReady(results,0);
    }
}

void SearchEngine::textCompletion(const QString &str)
{

    if(engine->isAvailable()){
        QtConcurrent::run(engine,&CLuceneHelper::search,str,0);
    } else {
        QList<IndexedDocument> results;
        emit searchFinished(0);
        emit onTextCompletionReady(results,0);
    }

}

SearchEngine *SearchEngine::instance()
{
    if (!s_instance)
        s_instance = new SearchEngine;
    return s_instance;
}

SearchEngine::~SearchEngine()
{
}


void SearchEngine::slotSearchFinish(const QList<IndexedDocument> &results, double tiempo)
{
    emit searchFinished(results.size());
    emit onSearchReady(results,tiempo);
}

void SearchEngine::slotTextCompletionFinish(const QList<IndexedDocument> &results, double tiempo)
{
    emit searchFinished(results.size());
    emit onTextCompletionReady(results,tiempo);
}

void SearchEngine::slotOnError(const int ErrType,const QString Msg,const QString OrgMsg){
    emit onError(ErrType,Msg,OrgMsg);
}



