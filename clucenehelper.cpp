#include <clucenehelper.h>
#include <CommonDefines.h>
#include <QFile>
#include <CLucene/queryParser/MultiFieldQueryParser.h>
#include <QMetaType>
#include <QRegExp>
#include <QDir>
#include <QMutex>
#include <QDebug>

//CL_NS_USE2(analysis, snowball);

#define IndexContent
#define IndexContentDebug1

TCHAR* QStringToTChar(const QString &str)
{
    TCHAR *string = new TCHAR[(str.length() +1) * sizeof(TCHAR)];
    memset(string, 0, (str.length() +1) * sizeof(TCHAR));
    str.toWCharArray(string);
    return string;
}

QString TCharToQString(const TCHAR *string)
{
    QString retValue = QString::fromWCharArray(string);
    return retValue;
}

CLuceneHelper *CLuceneHelper::s_instance = 0;

CLuceneHelper::CLuceneHelper(QObject *parent) :
    QObject(parent)/*,an(_T("Spanish"))*/
{
    qRegisterMetaType< QList<IndexedDocument> >( "QList<IndexedDocument>" );

    //SearchField = "CleanFileName";
    //MultiFieldSearch = false;
    dirIndex = "s_index";

    writer = NULL;
}

MagicFileInfo CLuceneHelper::GetMagicfileinfo(const QString &FileName)
{
    return MagicFileInfo(FileName);
}


CLuceneHelper::~CLuceneHelper(){
    _lucene_shutdown();
}

void CLuceneHelper::index(const QString &path) {


    QDir dir(path);                            //Opens the path
    QStringList FileTypes ;

    FileTypes <<  "*.cpp" ;
    QFileInfoList files = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files | QDir::Drives); //Gets the file information
    qDebug()<< "Cant: "<<files.count();


    try {


        if(writer == NULL){
            writer = _CLNEW IndexWriter(dirIndex.toLatin1().constData(),&an,true);
            //writer = _CLNEW IndexWriter("s_index",&an,true);
            writer->setMaxFieldLength(0x7FFFFFFFL);
            writer->setUseCompoundFile(false);
        }


        foreach(const QFileInfo &fi, files) {      //Loops through the found files.
            QString Path = fi.absoluteFilePath();  //Gets the absolute file path

            if(fi.isDir()) {
                index(Path);          //Recursively goes through all the directories.
            } else {
                //Do stuff with the found file.
                int size = FileTypes.size();
                for (int i = 0; i < size; ++i){
                    //QRegExp rx(FileTypes.at(i));
                    //rx.setPatternSyntax(QRegExp::Wildcard);
                    //if (rx.exactMatch(fi.fileName())){

                        TCHAR *TCharFilePath =  QStringToTChar(Path);
                        TCHAR *TCharFileName = QStringToTChar(fi.fileName());
                        TCHAR *TCharFileExt = QStringToTChar(fi.completeSuffix());
                        TCHAR *TCharCleanFileName = QStringToTChar(Path.replace(QRegExp("[^a-zA-Z0-9]+")," "));
                        Document doc;

                        QString native = QDir::toNativeSeparators(fi.absoluteFilePath());
                        MagicFileInfo f = this->GetMagicfileinfo(native);

                        qDebug() << "File: " << native;
                        qDebug() << "Charset: " << f.charset;
                        qDebug() << "Description: " << f.description;
                        qDebug() << "MimeType: " << f.mimeType;
                        qDebug() << "===================================";

                        //doc.add( *_CLNEW Field(_T("id"), Tcharid, Field::STORE_YES | Field::INDEX_UNTOKENIZED ) );
                        doc.add( *_CLNEW Field(_T("Path"), TCharFilePath, Field::STORE_YES | Field::INDEX_TOKENIZED ) );
                        doc.add( *_CLNEW Field(_T("FileName"),TCharFileName, Field::STORE_YES | Field::INDEX_TOKENIZED) );
                        doc.add( *_CLNEW Field(_T("FileType"),TCharFileExt, Field::STORE_YES | Field::INDEX_TOKENIZED) );
                        //doc.add( *_CLNEW Field(_T("MimeType"),TCharFileExt, Field::STORE_YES | Field::INDEX_TOKENIZED) );
                        doc.add( *_CLNEW Field(_T("CleanFileName"),TCharCleanFileName, Field::STORE_YES | Field::INDEX_TOKENIZED) );
                        writer->addDocument(&doc);

                        doc.clear();

                        delete [] TCharFilePath;
                        delete [] TCharFileName;
                        delete [] TCharFileExt;
                        delete [] TCharCleanFileName;

                        //qDebug() << Path;
                        //qDebug() <<  fi.completeSuffix();
                        //qDebug() <<  fi.fileName();
                        break;
                    //} //End Regex
                }
            }
        }


    } catch (CLuceneError err) {
        qDebug()<< toError(err.number()) << QString(err.what());
        emit onError(ErrLucene,toError(err.number()),QString(err.what()));
        emit indexContentFinished();
    }

}

void CLuceneHelper::optimize()
{
    if(writer!=NULL){
        writer->setUseCompoundFile(true);
        writer->optimize();
        writer->close();
        _CLLDELETE(writer)
    }
}


void CLuceneHelper::search(const QString &cad,size_t limite){

    QList<IndexedDocument> records;

    if(isAvailable()){

        QMutex mutex;
        mutex.lock();

        try {

            IndexReader * reader = IndexReader::open(dirIndex.toLatin1().constData(),false);
            IndexSearcher s(reader);

            Query* q;
            TCHAR *QueryString =  QStringToTChar(cad);


            const TCHAR* fields[] = {_T("Path"), _T("FileName"), _T("FileType"), _T("Category"), _T("CleanFileName"), NULL };
            MultiFieldQueryParser mfqp(fields, &an);

            q = mfqp.parse(QueryString);
            //MultiFieldSearch = false;

            int32_t i = 0;
            while ( fields[i] != NULL ){
                delete [] fields[i];
                i++;
            }


            LastQueryString = TCharToQString(q->toString());
            qDebug()<< "LastQueryString: "<< LastQueryString;
            delete [] QueryString;


            clock_t t1,t2;
            t1 = clock();
            Hits* h = s.search(q);

            size_t cant_doc =h->length();

            if(limite != 0)
                if(cant_doc > limite) cant_doc = limite;

            for ( size_t i=0;i<cant_doc;i++ ){
                Document* doc = &h->doc(i);


                IndexedDocument document;

                document.path=TCharToQString(doc->get(_T("Path")));
                document.fileName=TCharToQString(doc->get(_T("FileName")));
                document.extension=TCharToQString(doc->get(_T("FileType")));
                document.mimeType=TCharToQString(doc->get(_T("MimeType")));
                document.category=TCharToQString(doc->get(_T("Category")));

                records.append(document);
            }

            t2 = clock();
            double tiempo = double( t2 - t1 ) / (double)CLOCKS_PER_SEC;

            _CLLDELETE(h);
            _CLLDELETE(q);

            s.close();
            reader->close();

            _CLLDELETE(reader);

            emit onSearchFinish(records,tiempo);

        } catch (CLuceneError err) {
            QString StrExcept =  QString(err.what()).toUtf8();
            emit onError(ErrLucene,toError(err.number()),StrExcept);
            emit onSearchFinish(records,0);
        }

        mutex.unlock();

    } else {
        emit onError(ErrLucene,"El índice de búsqueda no es válido","");
        emit onSearchFinish(records,0);
    }
}

bool CLuceneHelper::isAvailable(){

    bool valid = true;

    if(!QFile::exists(dirIndex)){
        QString ErrStr = QString("El índice de búsqueda %1 no existe o está dañado").arg(dirIndex);
        emit onError(ErrFile,ErrStr,"");
        return false;
    }


    if(!IndexReader::indexExists(dirIndex.toLatin1().constData())){
        QString ErrStr = QString("El indice %1 no existe").arg(dirIndex);
        emit onError(ErrFile,ErrStr,"");
        return false;
    }

    return valid;
}

QString CLuceneHelper::cleanHtml(const QString &cad) const{

    QString textString;

    textString = cad;

    return textString.replace(QRegExp("<[^>]*>"),"");
}

QString CLuceneHelper::toError(int number) const {

    switch (number) {

    case  CL_ERR_IO :
        return QString("Error de entrada y salida.                                                                ");
        break;
    case  CL_ERR_NullPointer :
        return QString("Puntero nulo.                                                                             ");
        break;
    case  CL_ERR_Runtime :
        return QString("Error en tiempo de ejecución.                                                             ");
        break;
    case  CL_ERR_IllegalArgument :
        return QString("Argumento iválido.                                                                        ");
        break;
    case  CL_ERR_Parse :
        return QString("Consulta inválida.\nConsulte el manual de ayuda para las diferentes opciones de búsqueda");
        //return QString("Consulta inválida.                                                                        ");
        break;
    case  CL_ERR_TokenMgr :
        return QString("Error al reservar memoria para el token.                                               ");
        break;
    case  CL_ERR_UnsupportedOperation :
        return QString("Operación no soportada.                                                               ");
        break;
    case  CL_ERR_InvalidState :
        return QString("intenta acceder a un documento eliminado.                                             ");
        break;
    case  CL_ERR_IndexOutOfBounds :
        return QString("El índice de la matriz se encuentra fuera de los límites.                             ");
        break;
    case  CL_ERR_TooManyClauses :
        return QString("Error desconocido.                                                                    ");
        break;
    case  CL_ERR_RAMTransaction :
        return QString("Error de transacción en memoria.                                                      ");
        break;
    case  CL_ERR_InvalidCast :
        return QString("Error de conversión.                                                                  ");
        break;
    case  CL_ERR_IllegalState:    // Sub-error: AlreadyClosed
        return QString("Estado desconocido.                                                                   ");
        break;
    case  CL_ERR_UnknownOperator :
        return QString("Operador desconocido.                                                                 ");
        break;
    case  CL_ERR_ConcurrentModification :
        return QString("No es un número de hit válido.                                                        ");
        break;
    case  CL_ERR_CorruptIndex :
        return QString("El índice está corrupto.                                                              ");
        break;
    case  CL_ERR_NumberFormat :
        return QString("Error al formatear la cadena.                                                         ");
        break;
    case  CL_ERR_AlreadyClosed :
        return QString("El índice esta cerrado.                                                               ");
        break;
    case  CL_ERR_StaleReader :
        return QString("El índice está desactualizado  y ya no es válido para las operaciones de eliminación,\nrecuperación o la normalización.");
        break;
    case  CL_ERR_LockObtainFailed :
        return QString("Índice bloqueado para escritura.                                                       ");
        break;
    case  CL_ERR_Merge : //< Exception thrown if there are any problems while executing a merge.
        return QString("Error de mezcla de segmentos.                                                          ");
        break;
    case  CL_ERR_MergeAborted :
        return QString("Mezcla abortada.                                                                           ");
        break;
    case  CL_ERR_OutOfMemory :
        return QString("Fuera de memoria.                                                                          ");
        break;
    case  CL_ERR_FieldReader :
        return QString("Error al leer campo.                                                                       ");
        break;
    default:
        return QString("Error desconocido.                                                                         ");

    }

}

QStringList CLuceneHelper::getFieldNames() {

    try {

        QStringList FieldNames;
        StringArrayWithDeletor fn1;
        IndexReader * reader = IndexReader::open(dirIndex.toLatin1().constData(),false);

        reader->getFieldNames(IndexReader::INDEXED , fn1);
        reader->close();
        _CLLDELETE(reader);

        int fn1count = fn1.size();

        for (int n=0;n<fn1count;n++ ){
            QString flieldname = TCharToQString(fn1[n]);
            if(flieldname.compare("id")==0) continue;
            FieldNames.append(flieldname);
        }
        fn1.clear();

        return FieldNames;

    } catch (CLuceneError err) {
        emit onError(ErrLucene,toError(err.number()),QString(err.what()));
    }
    return QStringList();
}

QString CLuceneHelper::lastQuery() const{
    return LastQueryString;
}

void CLuceneHelper::setIndexDirectory(const QString &Dir)
{
    dirIndex = Dir + "s_index";
}

QString CLuceneHelper::getDirIndex() const
{
    return dirIndex;
}
