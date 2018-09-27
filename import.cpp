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

                "All Certificate Types (*.pfx,*.p12,*.cer,*.crt,*.p7b);;"
                "Personal Information Exchange(*.pfx,*.p12);;"
                "X.509 Certificate (*.cer,*.crt);;"
                "PKCS#7 Certificates (*.p7b);;"
                "All Types (*.*)"

                );

    QMessageBox::information(this,tr("File Name"), filename);
}
