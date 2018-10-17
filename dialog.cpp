#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent, QString CSR) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    _CSR = CSR;
    ui->setupUi(this);
    ui->displayCSR->setAlignment(Qt::AlignHCenter);
    ui->displayCSR->setText(_CSR);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_copyCSR_Btn_3_clicked()
{

    ui->displayCSR->selectAll();
    ui->displayCSR->copy();
    QMessageBox::information(this,tr("CSR"), "CSR Copied Successfully");

}

void Dialog::on_closeCSR_Btn_3_clicked()
{
    this->close();
}

void Dialog::on_saveCSR_Btn_3_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save CSR"), "C://",
                                                    tr("Privacy Enhanced Mail(*.pem);;"
                                                       "Text File (*.txt);;"));

    QFile file ( filename);

    if (file.open(QIODevice::ReadWrite)){
        QTextStream stream( &file );
        stream  << _CSR;
    }
    QMessageBox::information(this,tr("CSR"), "CSR Saved Successfully");

}
