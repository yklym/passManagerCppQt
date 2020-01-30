#include "getlinedialog.h"
#include "ui_getlinedialog.h"

GetLineDialog::GetLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetLineDialog)
{
    ui->setupUi(this);

    ui->lineEdit->setPlaceholderText("Your string");
}

GetLineDialog::~GetLineDialog()
{
    delete ui;
}
QString GetLineDialog::getLine(){
    return ui->lineEdit->text();
}
void GetLineDialog::on_pushButton_clicked()
{
    ui->lineEdit->setText(QString::fromStdString(pass_gen(6, false, true, false, false)));
}

void GetLineDialog::on_buttonBox_accepted()
{
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::information(this, "Error", "The field is empty");
        isEmpty_= true;
    }
    isEmpty_= false;
}
