#include "passGenSettingsDialog.h"
#include "ui_passGenSettingsDialog.h"
void passGenSettingsDialog::enableCheckBoxes(){
//    ui->checkBoxes->setEnabled(true);
    ui->checkBoxAlpha->setEnabled(true);
    ui->checkBoxDigits->setEnabled(true);
    ui->checkBoxCapital->setEnabled(true);
    ui->checkBoxChars->setEnabled(true);
    ui->spinBoxLength->setEnabled(true);
}
void passGenSettingsDialog::disableCheckBoxes(){
//    ui->checkBoxes->setEnabled(false);
    ui->checkBoxAlpha->setEnabled(false);
    ui->checkBoxDigits->setEnabled(false);
    ui->checkBoxCapital->setEnabled(false);
    ui->checkBoxChars->setEnabled(false);
    ui->spinBoxLength->setEnabled(false);
}
passGenSettingsDialog::passGenSettingsDialog(passSettings settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::passGenSettingsDialog)
{
    ui->setupUi(this);
    if(settings.alpha){ui->checkBoxAlpha->setChecked(true);}
//    this->parent()->settings.digits = true;
    if(settings.digits){ui->checkBoxDigits->setChecked(true);}
    if(settings.capital){ui->checkBoxCapital->setChecked(true);}
    if(settings.chars){ui->checkBoxAlpha->setChecked(true);}
    ui->radioButton_5->setChecked(true);
    ui->radioButtonUnbreakable->setChecked(false);
    ui->radioButtonStrong->setChecked(false);
    ui->radioButtonMedium->setChecked(false);
    ui->radioButtonWeak->setChecked(false);;
//    ui->spinBoxLength->setValue(settings.length);
//    ui->checkBoxes->setEnabled(true);

//    ui->checkBoxDigits->setChecked(false);
//    ui->checkBoxCapital->setChecked(false);
//    ui->checkBoxChars->setChecked(false);
//    ui->spinBoxLength->setValue(6);
}

passGenSettingsDialog::~passGenSettingsDialog()
{
    delete ui;
}
void passGenSettingsDialog::blockCheckBoxes(){
//    ui->groupBox->setEnabled(false);
    return;
}
void passGenSettingsDialog::on_radioButtonUnbreakable_clicked()
{
    ui->checkBoxes->setEnabled(true);
    ui->checkBoxAlpha->setChecked(true);
    ui->checkBoxDigits->setChecked(true);
    ui->checkBoxCapital->setChecked(true);
    ui->checkBoxChars->setChecked(true);
    ui->spinBoxLength->setValue(20);
    this->disableCheckBoxes();

}

void passGenSettingsDialog::on_radioButtonStrong_clicked()
{
    this->disableCheckBoxes();
    ui->checkBoxes->setEnabled(true);
    ui->checkBoxAlpha->setChecked(true);
    ui->checkBoxDigits->setChecked(true);
    ui->checkBoxCapital->setChecked(true);
    ui->checkBoxChars->setChecked(false);
    ui->spinBoxLength->setValue(12);
    this->disableCheckBoxes();

}

void passGenSettingsDialog::on_radioButtonMedium_clicked()
{
    this->disableCheckBoxes();
    ui->checkBoxes->setEnabled(true);
    ui->checkBoxAlpha->setChecked(true);
    ui->checkBoxDigits->setChecked(true);
    ui->checkBoxCapital->setChecked(false);
    ui->checkBoxChars->setChecked(false);
    ui->spinBoxLength->setValue(8);
    this->disableCheckBoxes();

}

void passGenSettingsDialog::on_radioButtonWeak_clicked()
{
    this->disableCheckBoxes();
    ui->checkBoxes->setEnabled(true);
    ui->checkBoxAlpha->setChecked(false);
    ui->checkBoxDigits->setChecked(true);
    ui->checkBoxCapital->setChecked(false);
    ui->checkBoxChars->setChecked(false);
    ui->spinBoxLength->setValue(6);
    this->disableCheckBoxes();

}
passSettings passGenSettingsDialog::getSettings(){
    passSettings retSettings;
    retSettings.alpha = ui->checkBoxAlpha->isChecked();
    retSettings.digits = ui->checkBoxDigits->isChecked();
    retSettings.capital = ui->checkBoxCapital->isChecked();
    retSettings.chars = ui->checkBoxChars->isChecked();
    retSettings.length = ui->spinBoxLength->value();
    return retSettings;
}
void passGenSettingsDialog::on_radioButton_5_clicked()
{
    //free checkboxes

    //---------------------
    this->enableCheckBoxes();
//    ui->checkBoxAlpha->setChecked(false);
//    ui->checkBoxDigits->setChecked(false);
//    ui->checkBoxCapital->setChecked(false);
//    ui->checkBoxChars->setChecked(false);
//    ui->spinBoxLength->setValue(1);
}
