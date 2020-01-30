#ifndef PASSGENSETTINGSDIALOG_H
#define PASSGENSETTINGSDIALOG_H
 #include <QDialog>
#include <passfunctions.h>

namespace Ui {
class passGenSettingsDialog;
}

class passGenSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit passGenSettingsDialog(passSettings settings, QWidget *parent = 0);
    ~passGenSettingsDialog();
    passSettings getSettings();

    void blockCheckBoxes();
private slots:
    void on_radioButtonUnbreakable_clicked();
    void on_radioButtonStrong_clicked();
    void enableCheckBoxes();
    void disableCheckBoxes();
    void on_radioButtonMedium_clicked();

    void on_radioButtonWeak_clicked();

    void on_radioButton_5_clicked();

private:
    passSettings settings;
    Ui::passGenSettingsDialog *ui;
};

#endif // PASSGENSETTINGSDIALOG_H
