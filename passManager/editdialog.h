#ifndef EDITDIALOG_H
#define EDITDIALOG_H
#include "user.h"
#include "account.h"
 #include <passfunctions.h>
#include "template.h"
#include <QDialog>
#include <QMessageBox>
#include "passGenSettingsDialog.h"
#include <QListWidgetItem>
#include<QListWidget>
#include <QWidget>
#include "virtual_storage.h"


namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    EditDialog(User currUser, virtual_storage  * stor, Service currService, QWidget *parent) ;
    explicit EditDialog(QWidget *parent = 0);
    ~EditDialog();
    void initSettings();
    bool isEdited(){
           return isEdited_;
       }
private slots:
//        void on_toolButton_clicked();
//         void on_pushButton_clicked();

//        void on_listWidget_itemClicked(QListWidgetItem *item);

//        void on_checkBox_clicked();

//        void on_pushButton_2_clicked();

//        void on_lineEditLogin_textEdited(const QString &arg1);

//        void on_lineEditPassword_textEdited(const QString &arg1);

//        void on_buttonBox_accepted();
    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_checkBox_clicked();

    void on_pushButton_2_clicked();

    void on_lineEditLogin_textEdited(const QString &arg1);

    void on_lineEditPassword_textEdited(const QString &arg1);

    void on_toolButton_clicked();

    void on_buttonBox_accepted();

private:
    void  updateTemplatesList();

    virtual_storage * stor;
    bool isEdited_;
    Service currService;
    passSettings settings;
    User currUser;
    bool isTemplate;
    Ui::EditDialog *ui;


};

#endif // EDITDIALOG_H



//    void on_toolButton_clicked();
//    void  updateTemplatesList();
//    void on_pushButton_clicked();

//    void on_listWidget_itemClicked(QListWidgetItem *item);

//    void on_checkBox_clicked();

//    void on_pushButton_2_clicked();

//    void on_lineEditLogin_textEdited(const QString &arg1);

//    void on_lineEditPassword_textEdited(const QString &arg1);

//    void on_buttonBox_accepted();

//private:
//
//    bool isAdded_;
//    Ui::AddDialog *ui;
//    SqliteStorage * stor;

//    User currUser;
//
//};

//#endif // ADD_DIALOG_H
