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


    importedString = readFileToString(filename.toStdString());

    std::cout << importedString << endl;
    if (TF_CERT_ERROR_INDEX){
        log_error();
        return;
    }

    TFCertificate *cert = new TFCertificate();
    cert->setCert(importedString);

    cert->insertDBCert(DB_FILE_NAME);

//    QString cert;

//    QFile file(filename);
//    QTextStream stream(&file);
//    if (file.open(QIODevice::ReadOnly)){
//        while(!stream.atEnd()){
//            cert.append(stream.readLine());
//        }
//    }



   // qDebug() <<certList;


  //  QMessageBox::information(this,tr("Certificate"), cert);
}
