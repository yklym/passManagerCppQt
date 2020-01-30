#include "add_dialog.h"
#include "ui_add_dialog.h"

 AddDialog::AddDialog(bool isTemplateMode, User currUser, virtual_storage * stor,QWidget *parent):
    isTemplateMode(isTemplateMode),
    currUser(currUser),
    stor(stor),
    QDialog(parent),
    ui(new Ui::AddDialog)
{

    ui->setupUi(this);
    this->setWindowTitle("Add Template");
    initSettings();
    ui->labelStrength->setVisible(false);
    this->updateTemplatesList();
    ui->groupBox_2->setVisible(false);
    ui->groupBox->move(5, 5);
    ui->textEdit_2->move(5, 250);
    ui->textEdit_2->setPlaceholderText("Description");
    ui->textEdit_2->resize(281, 71);
    ui->buttonBox->setVisible(false);


}
AddDialog::AddDialog(User currUser, virtual_storage * stor,QWidget *parent ) :
    currUser(currUser),
    stor(stor),
    QDialog(parent),
    ui(new Ui::AddDialog)
{


    ui->setupUi(this);
    initSettings();
    ui->labelStrength->setVisible(false);
    ui->pushButtonAddTemplate->setVisible(false);
    this->updateTemplatesList();
}

AddDialog::~AddDialog()
{
    delete ui;
}
void  AddDialog::initSettings(){
    this->settings.alpha = false;
    this->settings.digits = true;
    this->settings.capital = false;
    this->settings.chars = false;
    this->settings.length = 6;


}
void AddDialog::on_toolButton_clicked()
{
    passGenSettingsDialog dialog(this->settings, this);
    int status = dialog.exec();
    if(status){
        this->settings = dialog.getSettings();
    }else return;
}

void AddDialog::on_pushButton_clicked()
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

void AddDialog::updateTemplatesList(){

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

void AddDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    this->isTemplate = true;
    QVariant var = item->data(Qt::UserRole);
    Template acc = var.value<Template>();
    ui->lineEditLogin->setText( QString::fromStdString(acc.login));
    ui->lineEditPassword->setText( QString::fromStdString(acc.password));
    ui->labelStrength->setVisible(true);
    ui->labelStrength->setText(QString::fromStdString("<bold>"+acc.pass_strength+"</bold>"));
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

void AddDialog::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()){
        ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    } else {
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
    }

}
//add Template
void AddDialog::on_pushButton_2_clicked()
{
    if(this->isTemplate){
        return;
    }
    if(ui->lineEditPassword->text().length() < 1 || ui->lineEditLogin->text().length() < 1){
        QMessageBox::information(this, "Something got wrong ", "Template fields are empty!");

        return;
    }
    Template templ;
    templ.password = ui->lineEditPassword->text().toStdString();
    templ.login = ui->lineEditLogin->text().toStdString();
    templ.pass_strength =  convertEnumToString(checkStrength(templ.password));
    string desc = "Null";
    if(isTemplateMode && !ui->textEdit_2->toPlainText().isEmpty()){
        desc = ui->textEdit_2->toPlainText().toStdString();
    }
    templ.description = desc;
    this->stor->Sql_insertTemplate(this->currUser.id,templ);
    updateTemplatesList();
}

void AddDialog::on_lineEditLogin_textEdited(const QString &arg1)
{
    isTemplate = false;
}

void AddDialog::on_lineEditPassword_textEdited(const QString &arg1)
{
    isTemplate = false;
    ui->label_2->setText(QString::fromStdString(convertEnumToString(checkStrength(ui->lineEditPassword->text().toStdString()))));
    ui->labelStrength->setText(QString::fromStdString(convertEnumToString(checkStrength(ui->lineEditPassword->text().toStdString()))));

}

void AddDialog::on_buttonBox_accepted()
{
//    if(this->isTemplateMode){
//        return;
//    }
    Service serv;
    Account acc;
    if(ui->lineEditPassword->text().isEmpty() || ui->lineEditLogin->text().isEmpty() || ui->lineEdit->text().isEmpty()){
        QMessageBox::information(this, "Something got wrong ", "Some fields are empty!");
        isAdded_=false;
        return;

    }
    isAdded_=true;


    acc.login= ui->lineEditLogin->text().toStdString();
    acc.password= ui->lineEditPassword->text().toStdString();
    acc.pass_strength = ui->label_2->text().toStdString();
    acc.isTemplate = this->isTemplate;
    //    acc.id = ;
    int id = this->stor->insertAccount(acc);
    qDebug()<< "newAcc id:"<< id;

    if(ui->textEdit->toPlainText().isEmpty()){
        serv.description = "Null";
    }else  serv.description =ui->textEdit->toPlainText().toStdString();
    serv.name = ui->lineEdit->text().toStdString();
    serv.user_id = this->currUser.id;
    serv.account_id = id;
    int id2 =this->stor->insertService(serv);
    qDebug()<< "newServ id:"<< id2;


    acc.service_id = id2;
    this->stor->updateAccount(acc);

    return;


}

void AddDialog::on_pushButtonAddTemplate_clicked()
{
    this->close();
}
