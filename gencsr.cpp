#include "gencsr.h"
#include "ui_gencsr.h"
#include "dialog.h"


GenCSR::GenCSR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenCSR)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("QLabel {color : blue; }");
    ui->commonName_label_2->setStyleSheet("QLabel {color : red; }");
    ui->confirmPassword_label->setStyleSheet("QLabel {color : red; }");
    ui->password_label->setStyleSheet("QLabel {color : red; }");

    addKeySizesItems();

}


void GenCSR::addKeySizesItems()
{
    // qDebug() << "Adding Key Sizes Items" ;
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

    if  ( createPassword()){


        MainWindow conn;
        QString name,org,country,province,city;
        int keySize;


        keySize = ui->keySizesComboBox->currentText().toInt();

        gen_CSR();
    }

}

GenCSR::~GenCSR()
{
    delete ui;
}





bool GenCSR::createPassword()
{
    ui->password_label->clear();
    ui->confirmPassword_label->clear();

    if(!ui->password_private_key->text().isEmpty()){

        if(!ui->password_private_key->text().isEmpty() && !ui->confirm_password_private_key->text().isEmpty()) {

            if (!ui->password_private_key->text().compare(ui->confirm_password_private_key->text())) {

                ui->confirmPassword_label->setText("Password confirmation OK");
                return true;

            }
            else {
                ui->confirmPassword_label->setText("Passwords did not match, please try again");
                ui->confirm_password_private_key->clear();
                ui->password_private_key->clear();
                return false;

            }
        }
        else {
            ui->confirmPassword_label->setText("Confirm your password");
            return false;

        }

    }

    else if (ui->password_private_key->text().isEmpty() && !ui->confirm_password_private_key->text().isEmpty()) {
        ui->password_label->setText("Please enter a password first");
        ui->confirm_password_private_key->clear();
        return false;
    }

    else {
        ui->confirmPassword_label->setText("No Password Provided");
        return true;

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
        ui->commonName_label_2->setText("* Field Required");
       // QMessageBox::information(this,tr(""), "Please enter a common name");
        // this->close();
    }


    else{
        ui->label->setText("Generating CSR ...");
        std::string prvtKey = cert->generatePvtKey(keySize, password);
        cert->generateCSR(commonName);
        cert->insertDBCert(DB_FILE_NAME);

        if (TF_CERT_ERROR_INDEX) {
            std::cout << "failed\n";
        }
        log_error();


        this->hide();

        QString CSR = QString::fromStdString(cert->getCertReq());


        Dialog *CSRdisplay = new Dialog(this,CSR);
        CSRdisplay->show();
    }



}
