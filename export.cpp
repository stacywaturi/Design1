#include "export.h"
#include "ui_export.h"

Export::Export(QWidget *parent, int num) :
    QDialog(parent),
    ui(new Ui::Export)
{
    _num = num;


    ui->setupUi(this);

    ui->label_2->setStyleSheet("QLabel {color : blue; }");
    ui->exportFieldRequired_label_2->setStyleSheet("QLabel {color : red; }");
    ui->confirmPassword_label->setStyleSheet("QLabel {color : red; }");
    ui->password_label->setStyleSheet("QLabel {color : red; }");


}

bool Export::foundCertificate(){

    TFCertificate *cert = new TFCertificate();
    if(cert->lookupDBCert(DB_FILE_NAME, DB_COL_ID, std::to_string(_num))){
        if(QString::fromStdString(cert->getCert()).isEmpty()){
            QMessageBox::information(this,tr("Certificate"), "Could not find Certificate");
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

    password = ui->password_label->text().toStdString();


    TFCertificate *cert = new TFCertificate();

    // qDebug() <<"EXPORTING FILENAME" <<filename;
    // qDebug() << "EXPORTING PASSWORD" <<QString::fromStdString(password);


    if(cert->lookupDBCert(DB_FILE_NAME, DB_COL_ID, std::to_string(_num))){
        //  qDebug() <<"EXPORTING CERT" << QString::fromStdString(cert->getCert());

        if (createPassword()){


            if (!filename.isEmpty() && ui->pfx_radioButton->isChecked() ){
                bool exported =  cert->exportPFX(filename.toStdString(), password);
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
                    stream  << QString::fromStdString(cert->getCert());
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


