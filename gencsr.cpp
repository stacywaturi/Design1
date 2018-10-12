#include "gencsr.h"
#include "ui_gencsr.h"
#include "dialog.h"





GenCSR::GenCSR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenCSR)
{
    ui->setupUi(this);
    ui->confirmPassword_label->setStyleSheet("QLabel {color : blue; }");



    //    sqlite3 *db = openDatabase(DB_FILE_NAME, true);

    //    sqlite3_close(db);





    addKeySizesItems();

}


void GenCSR::addKeySizesItems()
{
    qDebug() << "Adding Key Sizes Items" ;
    ui->keySizesComboBox->setMaxVisibleItems(3);


    QFile file("C:/Users/Stacy/Documents/qt/Design1/keysizes.txt");


    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString line;

        while(!in.atEnd())
        {
            line = in.readLine();
            //qDebug() << line ;
            ui->keySizesComboBox->addItem(line);
        }
        in.flush();

        file.close ();
    }
}




void GenCSR::on_genCSRButton_clicked()
{
    ui->label->setText("Generating CSR ...");
    MainWindow conn;
    QString name,org,country,province,city;
    int keySize;


    keySize = ui->keySizesComboBox->currentText().toInt();

    gen_CSR();

}

GenCSR::~GenCSR()
{
    delete ui;
}


void GenCSR::on_create_password_privatekey_radioButton_clicked()
{
    ui->hBoxCreatePassword->setEnabled(true);

    ui->genCSRButton->setEnabled(false);


}

void GenCSR::on_createPassword_Btn_clicked()
{
    if(!ui->password_private_key->text().isEmpty()){
        if(!ui->password_private_key->text().isEmpty() && !ui->confirm_password_private_key->text().isEmpty()) {
            if (!ui->password_private_key->text().compare(ui->confirm_password_private_key->text())) {
                ui->confirmPassword_label->setText("Password confirmation OK");
                ui->genCSRButton->setEnabled(true);

            } else {
                ui->confirmPassword_label->setText("Passwords do not match, please try again");

            }
        } else {
            ui->confirmPassword_label->setText("Please fill 'Confirm Password' field");

        }
    } else {
        ui->confirmPassword_label->setText("Please fill password field");
    }
}

void GenCSR::on_pushButton_2_clicked()
{
    this->close();
}

void GenCSR::gen_CSR(){

    int keySize;
    std::string commonName,password = "";

    //get keysize and common name
    keySize = ui->keySizesComboBox->currentText().toInt();
    commonName = ui->commonName_lineEdit->text().toStdString();

    password = ui->password_private_key->text().toStdString();



    TFCertificate *cert = new TFCertificate();
    if (commonName.empty()){
        QMessageBox::information(this,tr(""), "Please enter a common name");
    }


    else{
        std::string prvtKey = cert->generatePvtKey(keySize, password);
        cert->generateCSR(commonName);
        cert->insertDBCert(DB_FILE_NAME);

        if (TF_CERT_ERROR_INDEX) {
            std::cout << "failed\n";
        }
        log_error();


    }

    this->hide();

    QString CSR = QString::fromStdString(cert->getCertReq());


    Dialog *CSRdisplay = new Dialog(this,CSR);
    CSRdisplay->show();

}
