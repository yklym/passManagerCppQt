#ifndef BMPREADERDIALOG_H
#define BMPREADERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <passfunctions.h>
#include <QDebug>


namespace Ui {
class BMPReaderDialog;
}

class BMPReaderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BMPReaderDialog(QWidget *parent = 0);
    ~BMPReaderDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::BMPReaderDialog *ui;
    char * exportImageDir;
};

#endif // BMPREADERDIALOG_H
