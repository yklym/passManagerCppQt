#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(User currUser, virtual_storage  * stor, Service currService, QWidget *parent) :
    QDialog(parent),
    currUser(currUser),
    stor(stor),
    currService(currService),
    ui(new Ui::EditDialog)
{

    ui->setupUi(this);
    initSettings();
    ui->textEdit->setText(QString::fromStdString(currService.description));
    ui->labelStrength->setVisible(false);
    ui->lineEdit->setText(QString::fromStdString(currService.name));
    Account acc = this->stor->Sql_getAccountByService(currService.account_id);

    ui->lineEditLogin->setText(QString::fromStdString(acc.login));
    ui->lineEditPassword->setText(QString::fromStdString(acc.password));
    this->updateTemplatesList();
}

EditDialog::~EditDialog()
{
    delete ui;
}


void  EditDialog::initSettings(){
    this->settings.alpha = false;
    this->settings.digits = true;
    this->settings.capital = false;
    this->settings.chars = false;
    this->settings.length = 6;


}


void EditDialog::updateTemplatesList(){

    //    this->hideLabels();

    ui->listWidget->clear();

    for(Template acc : this->stor->Sql_getAllTemplatesByUser(this->currUser.id) ){
        QVariant qVariant;
        //        qDebug() << "im in looooop!";
        qVariant.setValue(acc);
        QListWidgetItem *qServiceListItem = new QListWidgetItem();
        QString logo = QString::fromStdString(acc.login+" | "+acc.password+" | "+acc.pass_strength);
        qDebug() << "Giving accounts[" + logo+"]";
        qServiceListItem->setText(logo);
        qServiceListItem->setData(Qt::UserRole, qVariant);
        ui->listWidget->addItem(qServiceListItem);
    }
}
void EditDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    this->isTemplate = true;
    QVariant var = item->data(Qt::UserRole);
    Template acc = var.value<Template>();
    ui->lineEditLogin->setText( QString::fromStdString(acc.login));
    ui->lineEditPassword->setText( QString::fromStdString(acc.password));
    ui->labelStrength->setVisible(true);
    ui->labelStrength->setText(QString::fromStdString("<bold>"+acc.pass_strength+"</bold>"));
    ui->label_2->setText(QString::fromStdString("<bold>"+acc.pass_strength+"</bold>"));
    QString desc = QString::fromStdString(acc.description);
    if(desc=="Null"){
        ui->textBrowser->setText("No description");
    } else  ui->textBrowser->setText(desc);

    //    ui->label->setText("Name:  "+QString::fromStdString(serv.name));
    //----------------------------------------------------------------------------
    //    Account acc = this->stor->Sql_getAccountByService(serv.account_id);
    //    ui->label_2->setText("Login:  "+QString::fromStdString(acc.login) );
    //    ui->label_3->setText("Password:  "+ QString::fromStdString(acc.password));
    //-----------------------------------------------------------------------------
    //    if(serv.description=="NULL"){
    //         ui->textBrowser->setText("No description");
    //    }else  ui->textBrowser->setText(QString::fromStdString(serv.description));
}



//add Template


void EditDialog::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()){
        ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    } else {
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
    }
}

void EditDialog::on_pushButton_2_clicked()
{
    if(ui->lineEditPassword->text().length() < 1 || ui->lineEditLogin->text().length() < 1){
        QMessageBox::information(this, "Something got wrong ", "Template fields are empty!");

        return;
    }
    Template templ;
    templ.password = ui->lineEditPassword->text().toStdString();
    templ.login = ui->lineEditLogin->text().toStdString();
    templ.pass_strength =  convertEnumToString(checkStrength(templ.password));

    this->stor->Sql_insertTemplate(this->currUser.id,templ);
    updateTemplatesList();
}

void EditDialog::on_lineEditLogin_textEdited(const QString &arg1)
{
    isTemplate = false;
}

void EditDialog::on_lineEditPassword_textEdited(const QString &arg1)
{
    isTemplate = false;
    ui->label_2->setText(QString::fromStdString(convertEnumToString(checkStrength(ui->lineEditPassword->text().toStdString()))));
}

void EditDialog::on_toolButton_clicked()
{
    passGenSettingsDialog dialog(this->settings, this);
    int status = dialog.exec();
    if(status){
        this->settings = dialog.getSettings();
    }else return;
}
void EditDialog::on_pushButton_clicked()
{
    //    this->settings
    QString newPass = QString::fromStdString(pass_gen(this->settings.length,
                                                      this->settings.digits,
                                                      this->settings.alpha,
                                                      this->settings.capital,
                                                      this->settings.chars));
    ui->lineEditPassword->setText(newPass);
    ui->label_2->setText(QString::fromStdString(convertEnumToString(checkStrength(newPass.toStdString()))));
}

void EditDialog::on_buttonBox_accepted()
{
    Account acc;
   if(ui->lineEditPassword->text().isEmpty() || ui->lineEditLogin->text().isEmpty() || ui->lineEdit->text().isEmpty()){
       QMessageBox::information(this, "Something got wrong ", "Some fields are empty!");
       isEdited_=false;
       return;

   }
   isEdited_=true;

   if(ui->textEdit->toPlainText().isEmpty()){
       this->currService.description = "Null";
   }else  this->currService.description =ui->textEdit->toPlainText().toStdString();


   this->currService.name = ui->lineEdit->text().toStdString();
   this->currService.user_id = this->currUser.id;
   this->stor->updateService(this->currService);

    acc.id = this->currService.account_id;
   acc.login= ui->lineEditLogin->text().toStdString();
   acc.password= ui->lineEditPassword->text().toStdString();
   acc.pass_strength = ui->label_2->text().toStdString();
   acc.isTemplate = this->isTemplate;
   this->stor->updateAccount(acc);
//    acc.id = ;
//    int id =this->stor->insertAccount(acc);



//    acc.service_id = id2;
//    this->stor->updateAccount(acc);

   return;
}
