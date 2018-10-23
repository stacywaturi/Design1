#include "password.h"
#include "ui_password.h"
#include "export.h"

Password::Password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Password)
{
    ui->setupUi(this);
    ui->confirmPassword_label->setStyleSheet("QLabel {color : red; }");

}

void Password::checkPassword(){

    _password = ui->password_export_LineEdit->text();
    if (!_password.isEmpty()){
        // Use password to validate private key

    }

}

Password::~Password()
{
    delete ui;
}

void Password::on_pushButton_clicked()
{
    //this->close();
    checkPassword();


    Export *exportObj = new Export(this);
    if (_password == "123"){
        this->close();

        exportObj->setModal(true);
        exportObj->exec();

    }

    else
        ui->confirmPassword_label->setText("Incorrect Password");


}
