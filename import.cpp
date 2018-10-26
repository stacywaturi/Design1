#include "import.h"
#include "ui_import.h"
#include "tf_cert_util.h"

Import::Import(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Import)
{
    ui->setupUi(this);
}

Import::~Import()
{

    delete ui;
}

void Import::on_browseImport_Button_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All Certificate Types (*.pfx *.p12 *.cer *.crt *.p7b);;"
                "Personal Information Exchange(*.pfx, *.p12);;"
                "X.509 Certificate (*.cer, *.crt);;"
                "PKCS#7 Certificates (*.p7b);;"
                "All Types (*.*)"

                );


    std::string importedString;

    ui->import_lineEdit->setText(filename);


    importedString = readFileToString(filename.toStdString());


    if (TF_CERT_ERROR_INDEX){
        log_error();
        return;
    }

    TFCertificate *cert = new TFCertificate();
    cert->setCert(importedString);
    //cert->insertDBCert(DB_FILE_NAME);


    int a = cert->searchDBCert(DB_FILE_NAME);
    switch(a){
    case -1:
        QMessageBox::information(this,tr("Certificate"), "There was an error");

        break;
    case 0:
        QMessageBox::information(this,tr("Certificate"), "No matching CSR/Private key found!");

        break;
    case 1:
        if(cert->updateDBCert(DB_FILE_NAME)){

            QMessageBox::information(this,tr("Certificate"),"Certificate found and updated");

            ui->okImport_Btn->setEnabled(true);
        }
        else
            QMessageBox::information(this,tr("Certificate"),"Certificate found but failed to update");

        break;
    case 2:
        QMessageBox::information(this,tr("Certificate"),"The certificate already exists in the database");

        break;
    }

}

void Import::on_okImport_Btn_clicked()
{
    this->close();
}

void Import::on_cancelImprt_Btn_clicked()
{
    this->close();
}
