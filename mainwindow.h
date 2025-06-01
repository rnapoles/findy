#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QDockWidget>
#include <QStandardItemModel>
#include <searchengine.h>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QDockWidget *CategoryContainer;
    QListView *CategoryList;
    QSize oldMaxSize, oldMinSize;
    QStandardItemModel CategoryItemsModel;
    SearchEngine *SEngine;

    void setupCategory();
    void setDockSize(QDockWidget *dock, int, int);

    void setupSearchEngine();

private slots:
    void returnToOldMaxMinSizes();

    void searchStarted();
    void searchFinished(int size);
    void onTextCompletionReady(const QList<IndexedDocument>& results,double time);
    void onSearchReady(const QList<IndexedDocument>& results,double tiempo);
    void onError(const int ErrType,const QString Msg,const QString OrgMsg);
    void onWebPagelinkHovered( const QString & link, const QString & title, const QString & textContent );

    void on_searchButton_clicked();
    void on_actionCategor_as_triggered();
    void on_webView_linkClicked(const QUrl &arg1);
    void on_actionIndexar_triggered();
};

#endif // MAINWINDOW_H
