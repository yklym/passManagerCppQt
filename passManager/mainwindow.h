#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include "storage.hpp"
#include "virtual_storage.h"
 #include "editdialog.h"
#include <user.h>
#include <authorization_dialog.h>
#include <QFileDialog>
#include <QMessageBox>
#include <algorithm>
#include "bmpreaderdialog.h"
#include <passfunctions.h>

#include <QMainWindow>
#include <QListWidgetItem>
#include "add_dialog.h"
#include "getlinedialog.h"
#include "registerdialog.h"
#include <QDomDocument>
#include "importtemplatesdialog.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void updateServiceList();
    void updateTemplatesList();
    bool setWidgetsEnabled(bool flag);
    void hideLabels();
    void updatePagesLabel();
    void updateServiceListPages();
    void hideLabelsTemplates();
    void showLabels();
    void showLabelsTemplates();
    ~MainWindow();
    void  updateServiceListByName(string chars);
    void  updateTemplatesListByName(string chars);


private slots:
    void on_pushButton_clicked();
//    void openFile();
    void Quit();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButtonAdd_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonDelete_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButtonRegister_clicked();

    void on_pushButtonDeleteTemplates_clicked();

    void on_pushButtonEditTemplates_clicked();

    void on_lineEditTemplatesSearch_textEdited(const QString &arg1);

    void on_pushButtonTemplatesSearchClear_clicked();

    void on_listWidgetTemplates_itemClicked(QListWidgetItem *item);

    void on_pushButtonAddTemplates_clicked();


    void on_pushButtonExport_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();


    void on_pushButtonNextPage_clicked();

    void on_pushButtonPrevPage_clicked();
    void downloadFinished(QNetworkReply *reply);

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
//    SqliteStorage * stor;
    virtual_storage * stor;
    User currUser;
    int currPage;
    float  currServiceNumber;
    int currPageSize;
};

#endif // MAINWINDOW_H
