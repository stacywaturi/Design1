#include "export.h"
#include "ui_export.h"

Export::Export(QWidget *parent, int num) :
    QDialog(parent),
    ui(new Ui::Export)
{

    ui->setupUi(this);
    _num = num;

    qDebug() << "SELECTED ROW " <<_num;
}

Export::~Export()
{
    delete ui;
}


void Export::on_export_Button_clicked()
{

    ui->label_2->setText("Exporting Certificate...");

    std::string password = "";

    password = ui->password_export_3->text().toStdString();


    TFCertificate *cert = new TFCertificate();

    qDebug() <<"EXPORTING FILENAME" <<filename;
    qDebug() << "EXPORTING PASSWORD" <<QString::fromStdString( password);


    if(cert->lookupDBCert(DB_FILE_NAME, DB_COL_ID, std::to_string(_num))){
        qDebug() <<"EXPORTING CERT" << QString::fromStdString(cert->getCert());

        if(QString::fromStdString(cert->getCert()).isEmpty()){
            QMessageBox::information(this,tr("Certificate"), "Could not find Certificate");
        }
        else{
            bool exported =  cert->exportPFX(filename.toStdString(),password);
            if(exported)
                QMessageBox::information(this,tr("Certificate"), "Certificate Exported");
            else
                QMessageBox::information(this,tr("Certificate"), "Certificate Could not be Exported");
            log_error();

        }


    }

    this->close();




}

void Export::on_create_password_exportCert_radioButton_clicked()
{
    ui->hBoxCreatePasswordExport->setEnabled(true);

    ui->export_Button->setEnabled(false);


}

void Export::on_createPassword_Btn_3_clicked()
{
    if(!ui->password_export_3->text().isEmpty()){
        if(!ui->password_export_3->text().isEmpty() && !ui->confirm_password_export_3->text().isEmpty()) {
            if (!ui->password_export_3->text().compare(ui->confirm_password_export_3->text())) {
                ui->confirmPassword_label_3->setText("Password confirmation OK");
                ui->export_Button->setEnabled(true);

            } else {
                ui->export_Button->setEnabled(false);
                ui->confirmPassword_label_3->setText("Passwords do not match, please try again");

            }
        } else {
            ui->export_Button->setEnabled(false);
            ui->confirmPassword_label_3->setText("Please fill 'Confirm Password' field");

        }
    } else {
        ui->export_Button->setEnabled(false);
        ui->confirmPassword_label_3->setText("Please fill password field");
    }
}



void Export::on_browseExport_Button_clicked()
{
    filename = "";
    filename = QFileDialog::getSaveFileName(this,
                                            tr("Save CSR"), "C://",
                                            tr("Privacy Enhanced Mail(*.pfx);;"));

    ui->export_lineEdit->setText(filename);

}
