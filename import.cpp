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

    qDebug() << filename;
    std::string importedString;

    ui->import_lineEdit->setText(filename);


    importedString = readFileToString(filename.toStdString());

    //std::cout << importedString << endl;
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
        //cout<<"There was an error"<<endl;
        break;
    case 0:
            QMessageBox::information(this,tr("Certificate"), "No matching CSR/Private key found!");
        //cout<<"No matching csr/Private key found!"<<endl;
        break;
    case 1:
        if(cert->updateDBCert(DB_FILE_NAME)){
            QMessageBox::information(this,tr("Certificate"),"Certificate found and updated");
            //cout<<"certificate found and updated"<<endl;
            ui->okImport_Btn->setEnabled(true);
        }
        else
            QMessageBox::information(this,tr("Certificate"),"Certificate found but failed to update");
        // cout<<"certificate found but failed to update"<<endl;
        break;
    case 2:
        QMessageBox::information(this,tr("Certificate"),"The certificate already exists in the database");
        //cout<<"The certificate already exists in the database"<<endl;
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
