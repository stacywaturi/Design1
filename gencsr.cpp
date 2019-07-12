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

    QSize size(2,2);
    icon1.addFile(":/eyeOff",size);
    icon2.addFile(":/eyeOn", size);

    addKeySizesItems();
    showPassword();

}
void GenCSR::showPassword(){

    QAction *action = ui->password_private_key->addAction(icon1, QLineEdit::TrailingPosition);
    QAction *action2 = ui->confirm_password_private_key->addAction(icon1, QLineEdit::TrailingPosition);

    button = qobject_cast<QToolButton *>(action->associatedWidgets().last());
    button2 = qobject_cast<QToolButton *>(action2->associatedWidgets().last());

    connect(button, &QToolButton::pressed, this, &GenCSR::onPressed);
    connect(button, &QToolButton::released, this, &GenCSR::onReleased);

    connect(button2, &QToolButton::pressed, this, &GenCSR::onPressed);
    connect(button2, &QToolButton::released, this, &GenCSR::onReleased);

}

void GenCSR::onPressed(){
    QToolButton *button = qobject_cast<QToolButton *>(sender());

    button->setIcon(icon2);

    ui->password_private_key->setEchoMode(QLineEdit::Normal);
    ui->confirm_password_private_key->setEchoMode(QLineEdit::Normal);

}

void GenCSR::onReleased(){
    QToolButton *button = qobject_cast<QToolButton *>(sender());

    button->setIcon(icon1);

    ui->password_private_key->setEchoMode(QLineEdit::Password);
    ui->confirm_password_private_key->setEchoMode(QLineEdit::Password);

}

void GenCSR::addKeySizesItems()
{
    // qDebug() << "Adding Key Sizes Items" ;
    ui->keySizesComboBox->setMaxVisibleItems(3);

    QStringList keylist = {"2048 (default)","3072","4096"};
    ui->keySizesComboBox->addItems(keylist);
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
          //  std::cout << "failed\n";
        }
        log_error();


        this->hide();

        QString CSR = QString::fromStdString(cert->getCertReq());


        Dialog *CSRdisplay = new Dialog(this,CSR);
        CSRdisplay->show();
    }




}
