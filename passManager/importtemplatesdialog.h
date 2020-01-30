#ifndef IMPORTTEMPLATESDIALOG_H
#define IMPORTTEMPLATESDIALOG_H
#include <vector>
#include <QDialog>
#include "template.h"
#include <passfunctions.h>
#include "user.h"
 #include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include "virtual_storage.h"
namespace Ui {
class ImportTemplatesDialog;
}

class ImportTemplatesDialog : public QDialog
{
    Q_OBJECT

public:

    explicit ImportTemplatesDialog(User user ,virtual_storage * stor,vector<Template> Cifred, QWidget *parent = 0);
    ~ImportTemplatesDialog();
    void updateTemplatesList(vector<Template> vec);
private slots:
    void on_pushButtonDeCifre_clicked();

    void on_buttonBox_accepted();

private:
    User user;
    virtual_storage * stor;
    Ui::ImportTemplatesDialog *ui;
    vector<Template> Ciphred;
    vector<Template> deCifred;
};

#endif // IMPORTTEMPLATESDIALOG_H
