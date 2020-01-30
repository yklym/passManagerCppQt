#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "user.h"
#include <QMessageBox>
 #include "registerdialog.h"
#include <passfunctions.h>
#include "virtual_storage.h"
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(virtual_storage * stor, QWidget *parent = 0);
    ~RegisterDialog();
    User getUser();
    bool isAuthorized(){
        return isAuthorized_;
    }
private slots:
    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_buttonBox_accepted();

private:
    bool isAuthorized_;
    int id;
    virtual_storage * stor;
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
