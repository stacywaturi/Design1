#include "export.h"
#include "dialog.h"
#include "ui_export.h"

Export::Export(QWidget *parent, int num, TFCertificate *cert) :
    QDialog(parent),
    ui(new Ui::Export)
{
    _num = num;
    _cert = cert;

 //   qDebug()<< QString::fromStdString( _cert->getInfo());


    ui->setupUi(this);

    ui->label_2->setStyleSheet("QLabel {color : blue; }");
    ui->exportFieldRequired_label_2->setStyleSheet("QLabel {color : red; }");
    ui->confirmPassword_label->setStyleSheet("QLabel {color : red; }");
    ui->password_label->setStyleSheet("QLabel {color : red; }");

    showPassword();


}


void Export::showPassword(){

    QAction *action = ui->password_export_LineEdit->addAction(QIcon(":/eyeOff"), QLineEdit::TrailingPosition);
    QAction *action2 = ui->confirm_password_export_lineEdit->addAction(QIcon(":/eyeOff"), QLineEdit::TrailingPosition);

    button = qobject_cast<QToolButton *>(action->associatedWidgets().last());
    button2 = qobject_cast<QToolButton *>(action2->associatedWidgets().last());

    connect(button, &QToolButton::pressed, this, &Export::onPressed);
    connect(button, &QToolButton::released, this, &Export::onReleased);

    connect(button2, &QToolButton::pressed, this, &Export::onPressed);
    connect(button2, &QToolButton::released, this, &Export::onReleased);

    button = qobject_cast<QToolButton* >(action->associatedWidgets().last());
}

void Export::onPressed(){
    QToolButton *button = qobject_cast<QToolButton *>(sender());

    button->setIcon(QIcon(":/eyeOn"));

    ui->password_export_LineEdit->setEchoMode(QLineEdit::Normal);
    ui->confirm_password_export_lineEdit->setEchoMode(QLineEdit::Normal);

}

void Export::onReleased(){
    QToolButton *button = qobject_cast<QToolButton *>(sender());

    button->setIcon(QIcon(":/eyeOff"));

    ui->password_export_LineEdit->setEchoMode(QLineEdit::Password);
    ui->confirm_password_export_lineEdit->setEchoMode(QLineEdit::Password);

}

bool Export::foundCertificate(){

    TFCertificate *cert = new TFCertificate();
    if(cert->lookupDBCert(DB_FILE_NAME, DB_COL_ID, std::to_string(_num))){
        if(QString::fromStdString(cert->getCert()).isEmpty()){
            QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel {min-width:300px; font-size: 12px;}");
            msgBox.setText("This certificate is not available.");
            msgBox.setInformativeText("Do you want to view the Certificate Signing Request?");
            msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No );
            msgBox.setDefaultButton(QMessageBox::Yes);
            int ret = msgBox.exec();

            if(ret == QMessageBox::Yes)
            {
          //  QMessageBox::information(this,tr("Certificate"), "Certificate not available, \nPress OK to View/Save CSR");

            QString CSR = QString::fromStdString(cert->getCertReq());
            Dialog *CSRdisplay = new Dialog(this,CSR);
            CSRdisplay->show();
            }

            else {
                this->close();
            }

            return false;

        }
    }

    else
        return true;

}

Export::~Export()
{
    delete ui;
}


void Export::on_export_Button_clicked()
{
    std::string password = "";

    password = ui->password_export_LineEdit->text().toStdString();


   // qDebug()<< QString::fromStdString( _cert->getInfo());


    if (createPassword()){


        if (!filename.isEmpty() && ui->pfx_radioButton->isChecked() ){
            bool exported =  _cert->exportPFX(filename.toStdString(), password);
            if(exported)
                QMessageBox::information(this,tr("Certificate"), "Certificate Exported as .pfx");
            else
                QMessageBox::information(this,tr("Certificate"), "Certificate could not be Exported");
            log_error();
            this->close();

        }

        else if (!filename.isEmpty() && !ui->pfx_radioButton->isChecked()){

            QFile file (filename);

            if (file.open(QIODevice::ReadWrite)){
                QTextStream stream( &file );
                stream  << QString::fromStdString(_cert->getCert());
                QMessageBox::information(this,tr("Certificate"), "Certificate Exported Successfully");
            }

            else {

                QMessageBox::information(this,tr("Certificate"), "Certificate NOT Exported");
            }
            log_error();
            this->close();
        }



        else if (filename.isEmpty()){

            ui->exportFieldRequired_label_2->setText("*Required Field");
        }
    }

    else{
        //  QMessageBox::information(this,tr("Certificate"), "Could not not find Certificate");

    }


}

void Export::on_create_password_exportCert_radioButton_clicked()
{
    ui->hBoxCreatePasswordExport->setEnabled(true);

    ui->export_Button->setEnabled(false);


}

bool Export::createPassword()
{
    ui->password_label->clear();
    ui->confirmPassword_label->clear();

    if(!ui->password_export_LineEdit->text().isEmpty()){

        if(!ui->password_export_LineEdit->text().isEmpty() && !ui->confirm_password_export_lineEdit->text().isEmpty()) {

            if (!ui->password_export_LineEdit->text().compare(ui->confirm_password_export_lineEdit->text())) {

                ui->confirmPassword_label->setText("Password confirmation OK");
                return true;

            }
            else {

                ui->confirmPassword_label->setText("Passwords did not match, please try again");
                ui->confirm_password_export_lineEdit->clear();
                ui->password_export_LineEdit->clear();
                return false;

            }
        }
        else {
            ui->confirmPassword_label->setText("Confirm your password");
            return false;

        }

    }

    else if (ui->password_export_LineEdit->text().isEmpty() && !ui->confirm_password_export_lineEdit->text().isEmpty()) {
        ui->password_label->setText("Please enter a password first");
        ui->confirm_password_export_lineEdit->clear();
        return false;
    }

    else {
        ui->confirmPassword_label->setText("No Password Provided");
        return true;

    }
}



void Export::on_browseExport_Button_clicked()
{
    filename = "";
    if(ui->pfx_radioButton->isChecked()){

        filename = QFileDialog::getSaveFileName(this,
                                                tr("Save Certificate"), "C://",
                                                tr("Privacy Enhanced Mail(*.pfx);;"));

        ui->export_lineEdit->setText(filename);
    }

    else {

        filename = QFileDialog::getSaveFileName(this,
                                                tr("Save Certificate"), "C://",
                                                tr("Text File(*.txt);;"));

        ui->export_lineEdit->setText(filename);
    }




}

void Export::on_pushButton_2_clicked()
{
    this->close();
}


