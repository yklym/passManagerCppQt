#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H
 #include <QDialog>
 #include "passGenSettingsDialog.h"
#include <passfunctions.h>
#include <QListWidgetItem>
#include<QListWidget>
#include <QWidget>
#include "virtual_storage.h"
#include<QDialog>
#include "virtual_storage.h"
#include<QMessageBox>
namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);


    AddDialog(User currUser, virtual_storage * stor,QWidget *parent = 0);
    AddDialog(bool isTemplateMode, User currUser, virtual_storage * stor,QWidget *parent = 0);

    void initSettings();
    ~AddDialog();
    bool isAdded(){
        return isAdded_;
    }

private slots:
    void on_toolButton_clicked();
    void  updateTemplatesList();
    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_checkBox_clicked();

    void on_pushButton_2_clicked();

    void on_lineEditLogin_textEdited(const QString &arg1);

    void on_lineEditPassword_textEdited(const QString &arg1);

    void on_buttonBox_accepted();

    void on_pushButtonAddTemplate_clicked();

private:
    bool isTemplateMode;
    bool isTemplate;
    bool isAdded_;
    Ui::AddDialog *ui;
    virtual_storage * stor;
    User currUser;
    passSettings settings;
};

#endif // ADD_DIALOG_H
