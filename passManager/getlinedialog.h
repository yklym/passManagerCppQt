#ifndef GETLINEDIALOG_H
#define GETLINEDIALOG_H

#include <QDialog>
#include <passfunctions.h>
#include <QMessageBox>
#include "virtual_storage.h"
#include "user.h"
namespace Ui {
class GetLineDialog;
}

class GetLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetLineDialog(QWidget *parent = 0);
    ~GetLineDialog();
    QString getLine();
    bool isEmpty(){
        return isEmpty_;
    }
private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

private:
    bool isEmpty_;
    bool isDeciphred;
    Ui::GetLineDialog *ui;
};

#endif // GETLINEDIALOG_H
