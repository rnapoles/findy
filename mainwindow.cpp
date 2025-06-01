#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QList>
#include <QStringList>
#include <QWebElement>
#include <QWebFrame>
#include <QWebPage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qApp->setStyle("plastique");
    QFile file(":/resources/qss/blue.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    //qApp->setStyleSheet(styleSheet);


    ui->setupUi(this);

    this->setupCategory();
    this->setupSearchEngine();

    QWebPage *page = ui->webView->page();
    page->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(page,SIGNAL(linkHovered(QString,QString,QString)),this,SLOT(onWebPagelinkHovered(QString,QString,QString)));


    this->showMaximized();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupCategory()
{
    CategoryList = new QListView;
    QSize IconSize;
    IconSize.setHeight(32);
    IconSize.setWidth(32);

    CategoryList->setIconSize(IconSize);

    CategoryContainer = new QDockWidget("Categorías");

//    QLabel *TitleBarLabel = new QLabel();
//    TitleBarLabel->setText("<b>Categorías</b>");

    CategoryContainer->setWidget(CategoryList);
    CategoryList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    addDockWidget(Qt::LeftDockWidgetArea,CategoryContainer);
    this->setDockSize(CategoryContainer,200,CategoryContainer->height());


    QStandardItem *item = new QStandardItem("Archivos");
    item->setIcon(QIcon(":/images/category/folder.png"));

    CategoryItemsModel.appendRow(item);

    item = new QStandardItem("Correos");
    item->setIcon(QIcon(":/images/category/folder_mail.png"));
    CategoryItemsModel.appendRow(item);

    item = new QStandardItem("Documentos");
    item->setIcon(QIcon(":/images/category/folder_txt.png"));
    CategoryItemsModel.appendRow(item);

    item = new QStandardItem("images");
    item->setIcon(QIcon(":/images/category/folder_images.png"));
    CategoryItemsModel.appendRow(item);

    item = new QStandardItem("Ficheros de Texto");
    item->setIcon(QIcon(":/images/category/folder_txt.png"));
    CategoryItemsModel.appendRow(item);

    item = new QStandardItem("Desarrollo");
    item->setIcon(QIcon(":/images/category/folder.png"));
    CategoryItemsModel.appendRow(item);

    item = new QStandardItem("Aplicaciones");
    item->setIcon(QIcon(":/images/category/folder_app.png"));

    //item->setIcon();
    //item->setData(id,Qt::UserRole);
    CategoryItemsModel.appendRow(item);
    CategoryList->setModel(&CategoryItemsModel);
}

void MainWindow::setDockSize(QDockWidget* dock, int setWidth,int setHeight)
{
    oldMaxSize=dock->maximumSize();
    oldMinSize=dock->minimumSize();

    if (setWidth>=0){
        if (dock->width()<setWidth){
            dock->setMinimumWidth(setWidth);
        } else {
            dock->setMaximumWidth(setWidth);
        }
    }

    if (setHeight>=0){
        if (dock->height()<setHeight){
            dock->setMinimumHeight(setHeight);
        } else {
            dock->setMaximumHeight(setHeight);
        }
    }

    QTimer::singleShot(1, this, SLOT(returnToOldMaxMinSizes()));
}

void MainWindow::setupSearchEngine()
{
    SEngine = SearchEngine::instance();

    connect(SEngine,SIGNAL(searchStarted()),this,SLOT(searchStarted()));
    connect(SEngine,SIGNAL(searchFinished(int)),this,SLOT(searchFinished(int)));
    connect(SEngine,SIGNAL(onSearchReady(QList<IndexedDocument>,double)),this,SLOT(onSearchReady(QList<IndexedDocument>,double)));
    connect(SEngine,SIGNAL(onTextCompletionReady(QList<IndexedDocument>,double)),this,SLOT(onTextCompletionReady(QList<IndexedDocument>,double)));
    connect(SEngine,SIGNAL(Error(int,QString,QString)),this,SLOT(onError(int,QString,QString)));

}


void MainWindow::returnToOldMaxMinSizes()
{
    CategoryContainer->setMinimumSize(oldMinSize);
    CategoryContainer->setMaximumSize(oldMaxSize);
}


void MainWindow::on_searchButton_clicked()
{
    SEngine->search(ui->SearchLineEdit->text());

}

void MainWindow::searchStarted()
{
    ui->SearchButton->setEnabled(false);
    qDebug()<<"SearchStarted";
}

void MainWindow::searchFinished(int size)
{
    ui->SearchButton->setEnabled(true);
    qDebug()<<"SearchFinished";
    qDebug()<<size;
}

void MainWindow::onTextCompletionReady(const QList<IndexedDocument>& results,double time)
{
}

void MainWindow::onSearchReady(const QList<IndexedDocument>& results,double tiempo)
{
    ui->SearchButton->setEnabled(true);

    QString table;
    table =
    "<table width=\"100%\" border=\"0\">"
      "<tr>"
        "<td width=\"2%\"><img with='24' height='24' src='%4.png'></td>"
        "<td><a href='%3'><b>%1</b></a></td>"
      "</tr>"
      "<tr>"
        "<td>&nbsp;</td>"
        "<td>Resumen</td>"
      "</tr>"
      "<tr>"
        "<td>&nbsp;</td>"
            "<td><span style='text-transform:capitalize;'>%2</span> <span style='color: #009933'>%3</span> - <a href='%5' style='font-size:12px' onclick='javascript:alert(this.href)';>Abrir carperta</a> </td>"
      "</tr>"
    "</table>"
    "<br/>";

    //ui->webView->load(QUrl(":/resources/templates/index.html"));
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QWebElement body = frame->findFirstElement("body");

    QString Content;

    int size = results.size();
    for (int i = 0; i < size; ++i) {

        QString Path = results.at(i).path;
        QFileInfo FInfo(Path);

        QString Extension = results.at(i).extension;
        QString IconDir = qApp->applicationDirPath() + QDir::separator()+ "icons" + QDir::separator() + Extension;
        QString DirPath = FInfo.absoluteDir().absolutePath();

        QString info = table.arg(results.at(i).fileName).arg(Extension).arg(Path).arg(IconDir).arg(DirPath);
        Content.append(info);

       //qDebug()<< results.at(i).FileName;
    }

    //qDebug()<< Content;
    body.setInnerXml(Content);

    qDebug()<< body.tagName();
}

void MainWindow::onError(const int ErrType,const QString Msg,const QString OrgMsg){


    Q_UNUSED(ErrType);
    QMessageBox msgbox;
    msgbox.setText(Msg);
    msgbox.setDetailedText(OrgMsg);
    msgbox.setIcon(QMessageBox::Critical);
    msgbox.exec();

}



void MainWindow::on_actionCategor_as_triggered()
{
    CategoryContainer->show();
}

void MainWindow::on_webView_linkClicked(const QUrl &arg1)
{
    qDebug() << arg1;
}

void MainWindow::onWebPagelinkHovered( const QString & link, const QString & title, const QString & textContent ){
     this->statusBar()->showMessage(link);
}


void MainWindow::on_actionIndexar_triggered()
{
    SEngine->index();
}
