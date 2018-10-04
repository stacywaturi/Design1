#include "import.h"
#include "ui_import.h"

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

    QString cert;

    QFile file(filename);
    QTextStream stream(&file);
    if (file.open(QIODevice::ReadOnly)){
        while(!stream.atEnd()){
            cert.append(stream.readLine());
        }
    }

   // qDebug() <<certList;


    QMessageBox::information(this,tr("Raw Cert"), cert);
}
