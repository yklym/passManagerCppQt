#include "bmpreaderdialog.h"
#include "ui_bmpreaderdialog.h"

BMPReaderDialog::BMPReaderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BMPReaderDialog)
{
    ui->setupUi(this);
}

BMPReaderDialog::~BMPReaderDialog()
{
    delete ui;
}

void BMPReaderDialog::on_pushButton_clicked()
{
    QFileDialog tmpDialog(this);
    tmpDialog.setFileMode(QFileDialog::ExistingFile);
    tmpDialog.setNameFilter("*.bmp, *.BMP");

    //    tmpDialog.setFileMode(QFileDialog::Directory);
    QString dir = tmpDialog.getOpenFileName(
                this,
                "Import file",
                QDir::currentPath(),
                "*.bmp, *.BMP"
                /*QFileDialog::*/);
    QFile file( dir );
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this, "Some error occuried", "Cant open this file or folder");
        return;
    }
    file.close();
    ui->label->setAlignment(Qt::AlignCenter);
    QPixmap pix;

    /** to check wether load ok */
    if(pix.load(dir)){
        /** scale pixmap to fit in label'size and keep ratio of pixmap */
        pix = pix.scaled(ui->label->size(),Qt::KeepAspectRatio);
        ui->label->setPixmap(pix);
    }

    BMP *bmp = ReadBMP((char *)dir.toStdString().c_str());
    char * hiddenString =  ReadSecret(bmp);
    cout <<hiddenString;
    char * innuska = ReadSecretWord(bmp);
    cout << innuska;
    if (strcmp(innuska, "innuska") != 0) {
        ui->label_2->setText("\nNo secret data or file is broken\n");
    }
    else {
        ui->label_2->setText(QString::fromStdString(string(hiddenString)));
     }


}

void BMPReaderDialog::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::information(this, "Some error occuried", "Field is empty");
        return;
    }
    QFileDialog tmpDialog(this);
    tmpDialog.setFileMode(QFileDialog::ExistingFile);
    tmpDialog.setNameFilter("*.bmp, *.BMP");

    //    tmpDialog.setFileMode(QFileDialog::Directory);
    QString dir = tmpDialog.getOpenFileName(
                this,
                "Import file",
                QDir::currentPath(),
                "*.bmp, *.BMP"
                /*QFileDialog::*/);
    qDebug() <<dir;
    QFile file( dir );

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this, "Some error occuried", "Cant open this file or folder");
        return;
    }
    file.close();
    this->exportImageDir = dir.toLatin1().data();
    printf("Current path 2{%s}\n", this->exportImageDir);

    printf("Current path 3{%s}\n", this->exportImageDir);
    BMP *bmp = ReadBMP(this->exportImageDir);
//    qDebug() << QString::fromLatin1((char *)this->exportImageDir.toStdString().c_str());
//    qDebug() << QString::fromLatin1((char *)this->exportImageDir.toStdString().c_str());

    WriteSecretWord(bmp, "innuska");
    WriteSecret(bmp, ui->lineEdit->text().toLatin1().data());
    WriteBMP(this->exportImageDir, bmp);
    ui->lineEdit->clear();
    ui->lineEdit->setPlaceholderText("your secret");
//        qDebug() << "wrote successfuly "<<fileName;
}

void BMPReaderDialog::on_pushButton_3_clicked()
{
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::information(this, "Some error occuried", "Field is empty");
        return;
    }
    printf("Current path 3{%s}\n", this->exportImageDir);
    BMP *bmp = ReadBMP(this->exportImageDir);
//    qDebug() << QString::fromLatin1((char *)this->exportImageDir.toStdString().c_str());
//    qDebug() << QString::fromLatin1((char *)this->exportImageDir.toStdString().c_str());

    WriteSecretWord(bmp, "innuska");
    WriteSecret(bmp, ui->lineEdit->text().toLatin1().data());
    WriteBMP(this->exportImageDir, bmp);
//        qDebug() << "wrote successfuly "<<fileName;


}
