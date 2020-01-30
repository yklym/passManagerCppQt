#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(virtual_storage * stor, QWidget *parent) :
    QDialog(parent),
    stor(stor),
     ui(new Ui::RegisterDialog)
{

    ui->setupUi(this);
       isAuthorized_ = false;
        ui->label_2->setVisible(false);

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}
User RegisterDialog::getUser(){
    User us;
    us.id = id;
    us.username = ui->lineEdit->text().toStdString();
    us.password =  ui->lineEdit_2->text().toStdString();
    return us;
}

void RegisterDialog::on_lineEdit_2_textEdited(const QString &arg1)
{
    ui->label_2->setVisible(true);
    ui->label_2->setText(QString::fromStdString(convertEnumToString(checkStrength(ui->lineEdit_2->text().toStdString()))));

}

void RegisterDialog::on_buttonBox_accepted()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty()){
        QMessageBox::information(this, "Oops, something got wrong!", "All the fields must be filled");
        return;
    }
    if(ui->lineEdit_2->text()!=ui->lineEdit_3->text()){
        QMessageBox::information(this, "Oops, something got wrong!", "Your passwords differ");
        return;
    }
    User user;
    user.password = ui->lineEdit_2->text().toStdString();
    user.username = ui->lineEdit->text().toStdString();
    this->id = this->stor->Sql_insertUser(user)!=-1;
    if(this->id){
        isAuthorized_=true;
        return;

    }else{
        QMessageBox::information(this, "Oops, something got wrong!", "It seems this username is already taken");

        isAuthorized_ = false;
        return;
    }
}
