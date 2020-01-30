#include "authorization_dialog.h"
#include "ui_authorization_dialog.h"
#include <QMessageBox>

AuthorizationDialog::AuthorizationDialog(virtual_storage * stor, QWidget *parent) :
    QDialog(parent),
    stor(stor),
    ui(new Ui::AuthorizationDialog)
{

    this->isAuthorized_ = false;
    ui->setupUi(this);
}

User AuthorizationDialog::getUser(){
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
//    optional<User> us= this->stor->Sql_getUser(username, password);
        User us= this->stor->Sql_getUser(username.toStdString(), password.toStdString());
    if(us.id !=-1){
    return us;
    } else {
        User u;
        u.id = -1;
        return u;
    }

}
AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
}
bool AuthorizationDialog::isAuthorized(){
    if(this->isAuthorized_){
        return true;
    } else return false;
}
void AuthorizationDialog::on_buttonBox_accepted()
{
    QString username = ui->lineEditUsername->text() ;
    QString password = ui->lineEditPassword->text() ;
//    optional<User> us= this->stor->Sql_getUser(username, password);
        User us= this->stor->Sql_getUser(username.toStdString(), password.toStdString());
    qDebug()<<"Login:" <<ui->lineEditUsername->text();
    qDebug()<<"Password:" <<ui->lineEditPassword->text();
    if(us.id != -1){
        this->isAuthorized_= true;
        qDebug() <<"authorithation successful";
//        qDebug()<<"Login:" <<ui->lineEditUsername->text();
//        qDebug()<<"Password:" <<ui->lineEditPassword->text();
    } else {
           QMessageBox::information(this, "Authorization failed ", "Wrong username or password");
              qDebug() <<"Authorization failed ";
    }
}
