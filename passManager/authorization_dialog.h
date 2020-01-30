#ifndef AUTHORIZATION_DIALOG_H
#define AUTHORIZATION_DIALOG_H

#include <QDialog>
 #include "user.h"
#include "virtual_storage.h"


namespace Ui {
class AuthorizationDialog;
}

class AuthorizationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationDialog(QWidget *parent = 0);
    AuthorizationDialog( virtual_storage * stor, QWidget *parent = 0);
    User getUser();
    bool isAuthorized();
    ~AuthorizationDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AuthorizationDialog *ui;
    virtual_storage * stor;

    bool isAuthorized_;
};

#endif // AUTHORIZATION_DIALOG_H
