#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

void MainWindow::hideLabels(){
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->textBrowser->setVisible(false);
}
void MainWindow::hideLabelsTemplates(){
    ui->labelTemplates_1->setVisible(false);
    ui->labelTemplates_2->setVisible(false);
    ui->labelTemplates_3->setVisible(false);
    ui->textBrowserT->setVisible(false);
}

void MainWindow::showLabels(){
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->textBrowser->setVisible(true);
}
void MainWindow::showLabelsTemplates(){
    ui->labelTemplates_1->setVisible(true);
    ui->labelTemplates_2->setVisible(true);
    ui->labelTemplates_3->setVisible(true);
    ui->textBrowserT->setVisible(true);
}
void MainWindow::updateServiceListPages(){
    this->hideLabels();

    ui->pushButtonDelete->setEnabled(false);
    ui->pushButtonEdit->setEnabled(false);
    //Actions
    ui->actionDelete->setEnabled(false);
    ui->actionEdit->setEnabled(false);
    ui->listWidget->clear();

    if(ui->lineEdit->text().isEmpty()){
        this->currServiceNumber= this->stor->Sql_getServicesNumber(this->currUser.id);

        if(this->currPage  >= ceil(this->currServiceNumber/ this->currPageSize)){
            ui->pushButtonNextPage->setEnabled(false);
        }else {
            ui->pushButtonNextPage->setEnabled(true);
        }
        if(this->currPage <= 1){
            ui->pushButtonPrevPage->setEnabled(false);
        }else {
            ui->pushButtonPrevPage->setEnabled(true);
        }
        this->updatePagesLabel();

        for(Service serv : this->stor->Sql_getAllServicesByUserOffset(this->currUser.id,  this->currPageSize, (this->currPage-1) * this->currPageSize)){
            QVariant qVariant;
            //        qDebug() << "im in looooop!";
            qVariant.setValue(serv);
            QListWidgetItem *qServiceListItem = new QListWidgetItem();
            qServiceListItem->setText(QString::fromStdString(serv.name));
            qServiceListItem->setData(Qt::UserRole, qVariant);
            ui->listWidget->addItem(qServiceListItem);
        }
    }else {
        string tmpStr = ui->lineEdit->text().toStdString();

        this->currServiceNumber= this->stor->Sql_getServicesNumberSearch(this->currUser.id, tmpStr);
        qDebug() <<this->currServiceNumber;

        if(this->currPage  >= ceil(this->currServiceNumber/ this->currPageSize)){
            ui->pushButtonNextPage->setEnabled(false);
        }else {
            ui->pushButtonNextPage->setEnabled(true);
        }
        if(this->currPage <= 1){
            ui->pushButtonPrevPage->setEnabled(false);
        }else {
            ui->pushButtonPrevPage->setEnabled(true);
        }
        this->updatePagesLabel();
        for(Service serv : this->stor->Sql_getAllServicesByUserOffsetSearch(this->currUser.id,  this->currPageSize, (this->currPage-1) * this->currPageSize,  tmpStr)){
            QVariant qVariant;
            //        qDebug() << "im in looooop!";
            qVariant.setValue(serv);
            QListWidgetItem *qServiceListItem = new QListWidgetItem();
            qServiceListItem->setText(QString::fromStdString(serv.name));
            qServiceListItem->setData(Qt::UserRole, qVariant);
            ui->listWidget->addItem(qServiceListItem);
        }
    }

}

void MainWindow::updateServiceList(){

    this->hideLabels();
    ui->pushButtonDelete->setEnabled(false);
    ui->pushButtonEdit->setEnabled(false);
    //Actions
    ui->actionDelete->setEnabled(false);
    ui->actionEdit->setEnabled(false);
    ui->listWidget->clear();

    for(Service serv : this->stor->Sql_getAllServicesByUser(this->currUser.id)){
        QVariant qVariant;
        //        qDebug() << "im in looooop!";
        qVariant.setValue(serv);
        QListWidgetItem *qServiceListItem = new QListWidgetItem();
        qServiceListItem->setText(QString::fromStdString(serv.name));
        qServiceListItem->setData(Qt::UserRole, qVariant);
        ui->listWidget->addItem(qServiceListItem);
    }
}
void MainWindow::updateTemplatesList(){

    this->hideLabelsTemplates();

    //Actions
    ui->actionDelete_2->setEnabled(false);
    ui->actionEdit_2->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->pushButtonDeleteTemplates->setEnabled(false);
    ui->pushButtonEditTemplates->setEnabled(false);


    ui->listWidgetTemplates->clear();

    for(Template templ : this->stor->Sql_getAllTemplatesByUser(currUser.id)){
        QVariant qVariant;
        //        qDebug() << "im in looooop!";
        qVariant.setValue(templ);
        QListWidgetItem *qTemplateListItem = new QListWidgetItem();
        qTemplateListItem->setText(QString::fromStdString(templ.login+" || "+ templ.password + " || " + templ.pass_strength));
        qTemplateListItem->setData(Qt::UserRole, qVariant);
        ui->listWidgetTemplates->addItem(qTemplateListItem);
    }
}

bool MainWindow::setWidgetsEnabled(bool flag){
    ui->labelPassCheck->setVisible(flag);
    this->hideLabels();
    this->hideLabelsTemplates();
    ui->pushButtonAdd->setEnabled(flag);
    ui->pushButtonAddTemplates->setEnabled(flag);
    ui->pushButtonDelete->setEnabled(flag);
    ui->pushButtonDeleteTemplates->setEnabled(flag);
    ui->pushButtonEdit->setEnabled(flag);
    ui->pushButtonEditTemplates->setEnabled(flag);
    ui->pushButtonExport->setEnabled(flag);
    ui->pushButton_2->setEnabled(flag);
    ui->pushButton_4->setEnabled(flag);
    ui->pushButtonTemplatesSearchClear->setEnabled(flag);
    ui->lineEdit->setEnabled(flag);
    ui->lineEditTemplatesSearch->setEnabled(flag);
    //actions
    ui->actionAdd->setEnabled(flag);
    ui->actionadd->setEnabled(flag);
    ui->actionDelete->setEnabled(flag);
    ui->actionDelete_2->setEnabled(flag);
    ui->actionExport->setEnabled(flag);
    ui->actionImport->setEnabled(flag);
    ui->actionEdit->setEnabled(flag);
    ui->actionEdit_2->setEnabled(flag);
    ui->pushButton_6->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));

    this->stor = nullptr;


    //PAGINATION
    this->stor= new virtual_storage;
    this->currPage = 1;
    this->currPageSize = 2;
    this->currServiceNumber = 1;
    ui->pushButtonPrevPage->setEnabled(false);
    ui->pushButtonNextPage->setEnabled(false);

    if(!stor->load()){
        QMessageBox::information(this,"Couldnt open storage", "Some error occuried while opening database file or server is closed" );

    }
    //TEST
//    this->currUser.id = 0;
//    this->updateServiceListPages();
//    updatePagesLabel();



    //MENU
    ui->actionQuit->setShortcuts(QKeySequence::Quit);
    ui->actionQuit->setStatusTip(tr("Exit programm"));
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::Quit);

    ui->actionLog_in->setShortcut(QKeySequence(tr("Ctrl+L")));
    connect(ui->actionLog_in, &QAction::triggered, this, &MainWindow::on_pushButton_clicked);

    ui->actionRegister->setShortcut(QKeySequence(tr("Ctrl+R")));
    connect(ui->actionRegister, &QAction::triggered, this, &MainWindow::on_pushButtonRegister_clicked);


    connect(ui->actionAdd, &QAction::triggered, this, &MainWindow::on_pushButtonAdd_clicked);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::on_pushButtonEdit_clicked);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::on_pushButtonDelete_clicked);

    connect(ui->actionadd, &QAction::triggered, this, &MainWindow::on_pushButtonAddTemplates_clicked);
    connect(ui->actionEdit_2, &QAction::triggered, this, &MainWindow::on_pushButtonEditTemplates_clicked);
    connect(ui->actionDelete_2, &QAction::triggered, this, &MainWindow::on_pushButtonDeleteTemplates_clicked);

    connect(ui->actionImport, &QAction::triggered, this, &MainWindow::on_pushButton_2_clicked);
    connect(ui->actionExport, &QAction::triggered, this, &MainWindow::on_pushButtonExport_clicked);



    this->setWidgetsEnabled(false);


    //    ui->groupBoxButtons->setVisible(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Quit(){
    if(this->stor!=nullptr){
        this->stor->save();
    }

    this->close();
}
//void MainWindow::openFile(){

//    QFileDialog dialog(this);
//    dialog.setFileMode(QFileDialog::Directory);
//    QString dir = dialog.getExistingDirectory(
//                this,
//                "Open Folder",
//                QDir::currentPath(),
//                QFileDialog::ShowDirsOnly);
//    qDebug() << dir;


//    if(this->stor != nullptr){
//        this->stor->save();
//    }
//    SqliteStorage * str= new SqliteStorage(dir.toStdString()+"/");
//    this->stor= str;
//    if(!str->load()){
//        QMessageBox::information(this,"Couldnt open storage", "Some error occuried while opening file" );

//    }
//    if(this->currUser.id != -1){
//    }
//    qDebug() << "Opened file";


//    if(this->currUser.id !=-1){
//    }


//}
void MainWindow::on_pushButton_clicked()
{
    AuthorizationDialog dialog(this->stor, this);

    while(true){
        int status = dialog.exec();


        if((status == 1 && dialog.isAuthorized() )){
            this->currUser = dialog.getUser();
            qDebug() << "Curr username:"<<QString::fromStdString(this->currUser.username);
            qDebug() << "Curr user Id:"<<this->currUser.id;
            this->currPage = 1;
            updateServiceListPages();
            this->updateTemplatesList();
            QString newUserName = "user:\n<strong>" + QString::fromStdString(this->currUser.username)+"</strong>";
            this->ui->user_label->setText(newUserName);
            //                if(this->storage_ != nullptr){
            //                    ui->pushButton_4->setEnabled(true);
            //                }
            setWidgetsEnabled(true);
            ui->pushButtonDelete->setEnabled(false);
            ui->pushButtonDeleteTemplates->setEnabled(false);
            ui->pushButtonEditTemplates->setEnabled(false);
            ui->pushButtonEdit->setEnabled(false);
            //Actions
            ui->actionDelete->setEnabled(false);
            ui->actionDelete_2->setEnabled(false);
            ui->actionEdit_2->setEnabled(false);
            ui->actionEdit->setEnabled(false);
            return;
        }
        if(status == 0){
            return;
        }
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

    showLabels();
    QVariant var = item->data(Qt::UserRole);
    Service serv = var.value<Service>();

    ui->actionEdit->setEnabled(true);
    ui->actionDelete->setEnabled(true);
    ui->pushButtonEdit->setEnabled(true);
    ui->pushButtonDelete->setEnabled(true);

    ui->label->setText("Name:  "+QString::fromStdString(serv.name));
    //----------------------------------------------------------------------------
    Account acc = this->stor->Sql_getAccountByService(serv.account_id);
    ui->label_2->setText("Login:  "+QString::fromStdString(acc.login) );
    ui->label_3->setText("Password:  "+ QString::fromStdString(acc.password));
    ui->label_4->setText("Strength:" + QString::fromStdString(acc.pass_strength));
    //-----------------------------------------------------------------------------
    if(serv.description=="Null"){
        ui->textBrowser->setText("No description");
    }else  ui->textBrowser->setText(QString::fromStdString(serv.description));
}

void MainWindow::on_pushButtonAdd_clicked()
{
    AddDialog dialog(this->currUser, this->stor, this);
    int status;

    while(true){
        status   = dialog.exec();
        qDebug() << "been added:"<<dialog.isAdded();

        if(status == 1 && dialog.isAdded() ){
            break;
        }
        if(status == 0){
            return;
        }

    }
    if(status==1){

        this->currPage = 1;
        updateServiceListPages();
    }
}

void MainWindow::on_pushButtonEdit_clicked()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    QListWidgetItem * selectedItem = list.at(0);
    QVariant var = selectedItem->data(Qt::UserRole);
    Service serv = var.value<Service>();


    EditDialog dialog(this->currUser,  this->stor,serv, this);
    int status;
    while(true){

        status   = dialog.exec();

        if(status == 1 && dialog.isEdited() ){
            break;
        }
        if(status == 0){
            return;
        }
    }
    if(status==1){
        this->currPage = 1;
        updateServiceListPages();
        QList<QListWidgetItem *> newList = ui->listWidget->selectedItems();
        if(newList.count() == 0){return;}
        selectedItem = newList.at(0);


        QVariant var = selectedItem->data(Qt::UserRole);
        Service serv = var.value<Service>();
        ui->label->setText("Name:  "+QString::fromStdString(serv.name));
        //----------------------------------------------------------------------------
        Account acc = this->stor->Sql_getAccountByService(serv.account_id);
        ui->label_2->setText("Login:  "+QString::fromStdString(acc.login) );
        ui->label_3->setText("Password:  "+ QString::fromStdString(acc.password));
        ui->label_4->setText("Strength:" + QString::fromStdString(acc.pass_strength));
        //-----------------------------------------------------------------------------
        if(serv.description=="Null"){
            ui->textBrowser->setText("No description");
        }else  ui->textBrowser->setText(QString::fromStdString(serv.description));


    }
}

void MainWindow::on_pushButtonDelete_clicked()
{
    QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
    QListWidgetItem * selectedItem = list.at(0);
    QVariant var = selectedItem->data(Qt::UserRole);
    Service serv = var.value<Service>();

    //YES/NO

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm deleteing", "Do you want to delete\""+ QString::fromStdString(serv.name)+" \"service?" ,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->stor->removeAccount(serv.account_id);
        this->stor->removeService(serv.id);

        int itemRow = ui->listWidget->row(selectedItem);
        ui->listWidget->takeItem(itemRow);
        delete selectedItem;

        if(ui->listWidget->count()==0){
            this->currPage=1;
            this->updateServiceListPages();
            this->hideLabels();
            return;
        }else{

            //New labels
            QList<QListWidgetItem *> newList = ui->listWidget->selectedItems();

            selectedItem = newList.at(0);


            QVariant var = selectedItem->data(Qt::UserRole);
            Service serv = var.value<Service>();
            ui->label->setText("Name:  "+QString::fromStdString(serv.name));
            //----------------------------------------------------------------------------
            Account acc = this->stor->Sql_getAccountByService(serv.account_id);
            ui->label_2->setText("Login:  "+QString::fromStdString(acc.login) );
            ui->label_3->setText("Password:  "+ QString::fromStdString(acc.password));
            ui->label_4->setText("Strength:" + QString::fromStdString(acc.pass_strength));
            //-----------------------------------------------------------------------------
            if(serv.description=="Null"){
                ui->textBrowser->setText("No description");
            }else  ui->textBrowser->setText(QString::fromStdString(serv.description));

        }
    } else {
        qDebug() << "Yes was *not* clicked";
        return;
    }

}

void MainWindow::updateServiceListByName(string chars){

    this->hideLabels();
    ui->pushButtonDelete->setEnabled(false);
    ui->pushButtonEdit->setEnabled(false);
    //Actions
    ui->actionDelete->setEnabled(false);
    ui->actionEdit->setEnabled(false);

    ui->listWidget->clear();

    for(Service serv : this->stor->Sql_getAllServicesByUser(this->currUser.id)){
        string buf1 =  serv.name;
        string buf2 = chars;
        transform(buf1.begin(), buf1.end(), buf1.begin(), ::tolower);
        transform(buf2.begin(), buf2.end(), buf2.begin(), ::tolower);
        if (buf1.find(buf2) == std::string::npos) {
            continue;
        }
        QVariant qVariant;
        qVariant.setValue(serv);

        QListWidgetItem *qServiceListItem = new QListWidgetItem();
        qServiceListItem->setText(QString::fromStdString(serv.name));
        qServiceListItem->setData(Qt::UserRole, qVariant);
        ui->listWidget->addItem(qServiceListItem);
    }
}

void MainWindow::updateTemplatesListByName(string chars){

    this->hideLabelsTemplates();
    ui->pushButtonDeleteTemplates->setEnabled(false);
    ui->pushButtonEditTemplates->setEnabled(false);
    //Actions
    ui->actionDelete_2->setEnabled(false);
    ui->actionEdit_2->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);

    ui->listWidgetTemplates->clear();

    for(Template templ : this->stor->Sql_getAllTemplatesByUser(this->currUser.id)){
        string buf1 =  templ.login;
        string buf2 = chars;
        transform(buf1.begin(), buf1.end(), buf1.begin(), ::tolower);
        transform(buf2.begin(), buf2.end(), buf2.begin(), ::tolower);
        if (buf1.find(buf2) == std::string::npos) {
            continue;
        }
        QVariant qVariant;
        qVariant.setValue(templ);

        QListWidgetItem *qServiceListItem = new QListWidgetItem();
        qServiceListItem->setText(QString::fromStdString(templ.login+" || "+ templ.password + " || " + templ.pass_strength));
        qServiceListItem->setData(Qt::UserRole, qVariant);
        ui->listWidgetTemplates->addItem(qServiceListItem);
    }
}
void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    //            updateServiceListByName(arg1.toStdString());
    this->currPage = 1;
    this->updateServiceListPages();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->clear();
    this->currPage = 1;
    updateServiceListPages();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->labelPassCheck->setVisible(true);
    ui->labelPassCheck->setText(QString::fromStdString(convertEnumToString(checkStrength(ui->lineEditPassCheck->text().toStdString()))));
}

void MainWindow::on_pushButtonRegister_clicked()
{
    RegisterDialog dialog(this->stor, this);

    while(true){


        int status = dialog.exec();

        if(status == 1 && dialog.isAuthorized() ){
            this->currUser = dialog.getUser();
            this->currPage = 1;
            updateServiceListPages();
            QString newUserName = "user:\n" + QString::fromStdString(this->currUser.username);
            this->ui->user_label->setText(newUserName);
            return;
        }
        if(status == 0){
            return;
        }
    }

}

void MainWindow::on_pushButtonDeleteTemplates_clicked()
{
    QList<QListWidgetItem *> list = ui->listWidgetTemplates->selectedItems();
    QListWidgetItem * selectedItem = list.at(0);
    QVariant var = selectedItem->data(Qt::UserRole);
    Template templ = var.value<Template>();

    //YES/NO

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm deleteing", "Do you want to delete this template?" ,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        //----------------------------------------------------
        this->stor->Sql_removeTemplate(templ.id, this->currUser.id);


        int itemRow = ui->listWidgetTemplates->row(selectedItem);
        ui->listWidgetTemplates->takeItem(itemRow);
        delete selectedItem;

        if(ui->listWidgetTemplates->count()==0){

            this->hideLabelsTemplates();
            return;
        }else{

            //New labels
            QList<QListWidgetItem *> newList = ui->listWidgetTemplates->selectedItems();
            if(newList.count() == 0){
                return;

            }
            selectedItem = newList.at(0);


            QVariant var = selectedItem->data(Qt::UserRole);
            Template temp = var.value<Template>();

            ui->labelTemplates_1->setText("Login:  "+QString::fromStdString(temp.login));
            //----------------------------------------------------------------------------

            ui->labelTemplates_2->setText("Password:  "+ QString::fromStdString(temp.password));
            ui->labelTemplates_3->setText("Strength:" + QString::fromStdString(temp.pass_strength));
            //-----------------------------------------------------------------------------
            if(templ.description=="Null"){
                ui->textBrowser->setText("No description");
            }else  ui->textBrowserT->setText(QString::fromStdString(temp.description));
        }
    } else {
        qDebug() << "Yes was *not* clicked";
        return;
    }
}

void MainWindow::on_pushButtonEditTemplates_clicked()
{



}

void MainWindow::on_lineEditTemplatesSearch_textEdited(const QString &arg1)
{
    updateTemplatesListByName(arg1.toStdString());

}

void MainWindow::on_pushButtonTemplatesSearchClear_clicked()
{
    ui->lineEditTemplatesSearch->clear();
    updateTemplatesList();
}

void MainWindow::on_listWidgetTemplates_itemClicked(QListWidgetItem *item)
{
    showLabelsTemplates();
    QVariant var = item->data(Qt::UserRole);
    Template templ = var.value<Template>();
    ui->pushButton_6->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    ui->actionEdit_2->setEnabled(true);
    ui->actionDelete_2->setEnabled(true);
    ui->pushButtonEditTemplates->setEnabled(true);
    ui->pushButtonDeleteTemplates->setEnabled(true);

    ui->labelTemplates_1->setText("Login:  "+QString::fromStdString(templ.login));
    //----------------------------------------------------------------------------

    ui->labelTemplates_2->setText("Password:  "+ QString::fromStdString(templ.password));
    ui->labelTemplates_3->setText("Strength:" + QString::fromStdString(templ.pass_strength));
    //-----------------------------------------------------------------------------
    if(templ.description=="Null"){
        ui->textBrowserT->setText("No description");
    }else  ui->textBrowserT->setText(QString::fromStdString(templ.description));
}

void MainWindow::on_pushButtonAddTemplates_clicked()
{
    AddDialog dialog(true, this->currUser, this->stor, this);
    int status =     dialog.exec();
    this->updateTemplatesList();

}


QDomElement TemplateToXmlElement(QDomDocument & doc,struct Template & Template, const char * keyword){
    QDomElement elem = doc.createElement("template");
    elem.setAttribute("id", Template.id);
    elem.setAttribute("description", QString::fromStdString(Template.description));
    elem.setAttribute("login", QString::fromStdString(Template.login));

    //    const char * strKey = keyword.c_str();
    QString cipheredPass = QString::fromStdString(XorCodeEncode(Template.password.c_str(), keyword));
    elem.setAttribute("password", cipheredPass);
    elem.setAttribute("pass_strength", QString::fromStdString(Template.pass_strength));

    return elem;
}
Template XmlElementToTemplate(QDomElement & templateEl){

    Template templ;
    templ.id = templateEl.attribute("id").toInt();
    templ.description = templateEl.attribute("description").toStdString();
    templ.login = templateEl.attribute("login").toStdString();

    templ.password = templateEl.attribute("password").toStdString();
    templ.pass_strength = templateEl.attribute("pass_strength").toStdString();
    return templ;

}

void MainWindow::on_pushButtonExport_clicked()
{
    QFileDialog tmpDialog(this);
    tmpDialog.setFileMode(QFileDialog::Directory);
    QString dir = tmpDialog.getExistingDirectory(
                this,
                "Where to save",
                QDir::currentPath(),
                QFileDialog::ShowDirsOnly);


    QFile file( dir+"/" +QString::fromStdString(this->currUser.username) +"_templates.xml" );
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this, "Some error occuried", "Cant open this file or folder");
        return;
    }

    GetLineDialog dialog(this);
    while(true){
        int status = dialog.exec();
        if(status==1 && !dialog.isEmpty()){
            break;
        }
        if(status ==0){
            return;
        }
    }
    QString usersKey = dialog.getLine();
    //
    QDomDocument doc;
    QDomElement rootEl = doc.createElement("templates");

    for (Template & templ: this->stor->Sql_getAllTemplatesByUser(this->currUser.id)) {

        QDomElement serviceEl = TemplateToXmlElement(doc, templ, usersKey.toLatin1().data());
        rootEl.appendChild(serviceEl);
    }

    doc.appendChild(rootEl);
    //FILE




    QTextStream out(&file);
    out<<doc;
    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    QFileDialog tmpDialog(this);
    tmpDialog.setFileMode(QFileDialog::ExistingFile);
    //    tmpDialog.setFileMode(QFileDialog::Directory);
    QString dir = tmpDialog.getOpenFileName(
                this,
                "Import file",
                QDir::currentPath()
                /*QFileDialog::show*/);
    QFile file( dir );
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this, "Some error occuried", "Cant open this file or folder");
        return;
    }



    QTextStream in(&file);
    QString s = in.readAll();
    file.close();

    QDomDocument doc;
    QString errorMessage;
    QString qs =s;

    if (!doc.setContent(qs, &errorMessage)) {
        qDebug() << "error parsing xml: " << errorMessage;
        return ;
    }

    //    int id = 0;
    QDomElement rootEl = doc.documentElement();
    QDomNodeList rootElChildren = rootEl.childNodes();
    vector<Template> templVec;
    for (int i = 0; i < rootElChildren.length(); i++) {
        QDomNode templNode = rootElChildren.at(i);
        QDomElement templEl = templNode.toElement();
        Template templ = XmlElementToTemplate(templEl);
        templVec.push_back(templ);
    }
    ImportTemplatesDialog dial(this->currUser, this->stor,templVec, this);
    qDebug() << dial.exec();
    this->updateTemplatesList();

}

void MainWindow::on_pushButton_5_clicked()
{
    BMPReaderDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    string username = ui->lineEdit_2->text().toStdString();
    if(!this->stor->Sql_checkUser(username)){
        QMessageBox::information(this, "Error", "There is no such user");
        return;
    }
    QList<QListWidgetItem *> list = ui->listWidgetTemplates->selectedItems();
    QListWidgetItem * selectedItem = list.at(0);
    QVariant var = selectedItem->data(Qt::UserRole);
    Template templ = var.value<Template>();

    this->stor->Sql_insertTemplate(this->stor->Sql_checkUser(username), templ);
    QMessageBox::information(this, "Good job", "Shared successfuly!");


    //lineEdit2222
}
//PAGINATION
void MainWindow::on_pushButtonNextPage_clicked()
{
    this->currPage +=1;
    updatePagesLabel();
    //    ui->pushButtonPrevPage->setEnabled(true);
    //    if(this->currPage  >= ceil(this->currServiceNumber/ this->currPageSize)){
    //        ui->pushButtonNextPage->setEnabled(false);
    //    }
    this->updateServiceListPages();
}

void MainWindow::on_pushButtonPrevPage_clicked()
{
    this->currPage -=1;
    updatePagesLabel();
    //    if(this->currPage  <= 1 ){
    //        ui->pushButtonPrevPage->setEnabled(false);
    //    }
    this->updateServiceListPages();
}
void MainWindow::updatePagesLabel(){
    ui->labelPageNumber->setText(QString::number(this->currPage) + "/" + QString::number(ceil(this->currServiceNumber/this->currPageSize)));
}

void MainWindow::downloadFinished(QNetworkReply *reply)
{
    QPixmap pm;
    pm.loadFromData(reply->readAll());
    pm = pm.scaled(ui->label_5->size(),Qt::KeepAspectRatio);

    ui->label_5->setPixmap(pm);
}
void MainWindow::on_pushButton_7_clicked()
{
    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    connect(nam, &QNetworkAccessManager::finished, this, &MainWindow::downloadFinished);
    const QUrl url = QUrl("https://cataas.com/c");
    /*qDebug() <<QString::number(rand() % 1000)*/;
    QNetworkRequest request(url);
    nam->get(request);
}
