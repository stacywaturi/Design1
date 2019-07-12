#include "password.h"
#include "ui_password.h"
#include "export.h"

Password::Password(QWidget *parent, int num) :
    QDialog(parent),
    ui(new Ui::Password)
{
    _num = num;
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


void Password::on_OKBtn_clicked()
{
    //this->close();
    checkPassword();


    TFCertificate  *cert = new TFCertificate();

    cert->lookupDBCert(DB_FILE_NAME, DB_COL_ID, std::to_string(_num));
    //qDebug() << _num;
    //  qDebug()<< QString::fromStdString( cert->getInfo(INFO_ALL));

    if(cert->verifyPassword(_password.toStdString())){
        cert->setPassword(_password.toStdString());
      //  qDebug()<<"Successfully decrypted private key!"<<endl;


       this->close();
        Export *exportObj = new Export(this,_num,cert);

        exportObj->setModal(true);
        exportObj->exec();

    }

    else {
       // qDebug()<<"Passwords do not match! "<<endl;
        ui->confirmPassword_label->setText("Incorrect Password");
    }
}

void Password::on_cancelBtn_clicked()
{
    this->close();
}
