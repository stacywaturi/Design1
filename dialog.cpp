#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent, QString CSR) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    _CSR = CSR;
    ui->setupUi(this);
    ui->displayCSR->setText(_CSR);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_copyCSR_Btn_3_clicked()
{
    //  ui->displayCSR->copyAvailable(true);
    //  ui->displayCSR->
    ui->displayCSR->selectAll();
    ui->displayCSR->copy();

}

void Dialog::on_closeCSR_Btn_3_clicked()
{
    this->close();
}

void Dialog::on_saveCSR_Btn_3_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save CSR"), "C://",
                                                    tr("Text File (*.txt);;"));
    QFile file ( filename);

    if (file.open(QIODevice::ReadWrite)){
        QTextStream stream( &file );
        stream  << _CSR;
    }
}