#include "importtemplatesdialog.h"
#include "ui_importtemplatesdialog.h"

ImportTemplatesDialog::ImportTemplatesDialog(User user ,virtual_storage * stor,vector<Template> Cifred, QWidget *parent) :
    QDialog(parent),
    stor(stor),
    user(user),
    Ciphred(Cifred),
    ui(new Ui::ImportTemplatesDialog)
{
    ui->setupUi(this);

    updateTemplatesList(Ciphred);
}

ImportTemplatesDialog::~ImportTemplatesDialog()
{
    delete ui;
}

void ImportTemplatesDialog::updateTemplatesList(vector<Template> vec){

    //    this->hideLabels();

    ui->listWidget->clear();

    for(Template acc : vec ){
        QVariant qVariant;
        qDebug() << acc.id + "Hello";
        qVariant.setValue(acc);
        QListWidgetItem *qServiceListItem = new QListWidgetItem();
        QString logo = QString::fromStdString(acc.login+" | "+acc.password+" |["+acc.pass_strength+"]");
//        qDebug() << "Giving accounts[" + logo+"]";
        qServiceListItem->setText(logo);
        qServiceListItem->setData(Qt::UserRole, qVariant);
        ui->listWidget->addItem(qServiceListItem);
    }
}

void ImportTemplatesDialog::on_pushButtonDeCifre_clicked()
{
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::information(this, "Error", "Field is empty");
        return;
    }

    vector<Template> newVec = this->Ciphred;
    for(int i = 0; i < newVec.size(); i++){
        char * key = ui->lineEdit->text().toLatin1().data();

        Template tmpTempl = newVec[i];

        newVec[i].password = XorCodeEncode(tmpTempl.password.c_str(), key);
        qDebug() <<QString::fromStdString( tmpTempl.password) + "|" + QString::fromStdString(newVec[i].password) + "["+ ui->lineEdit->text()+"]";
    }
    this->updateTemplatesList(newVec);
}

void ImportTemplatesDialog::on_buttonBox_accepted()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation window", "Do you want to add these templates?" ,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "DSADASDSD";
        for(Template templ : this->deCifred){
            this->stor->Sql_insertTemplate(this->user.id, templ);
        }
        exit(2);
    }
}
