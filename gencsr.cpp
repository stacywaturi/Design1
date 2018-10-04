#include "gencsr.h"
#include "ui_gencsr.h"
#include "dialog.h"
int	TF_CERT_ERROR_INDEX = TF_CERT_no_error;
std::string	LOG_FILE_CERTMNGR	= "log_cert_mngr.log";
std::string  DB_FILE_NAME="test.db";

GenCSR::GenCSR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenCSR)
{
    ui->setupUi(this);

    openssl_init();

    ui->confirmPassword_label->setStyleSheet("QLabel {color : blue; }");
    MainWindow main_window;
    if (!main_window.DBConnOpen())
    {
        ui->label->setText("Failed to open DB");
    }
    else
        ui->label->setText("Connected to DB");

    //addCountryItems();
    addKeySizesItems();

}
//void genCSR::on_comboBox_clicked()

//void GenCSR::addCountryItems()
//{

//    qDebug() << "Adding Country Items" ;
//    ui->countryComboBox->setMaxVisibleItems(8);
//    //  ui->countryComboBox ->setEditable(true);

//    QFile file("C:/Users/Stacy/Documents/qt/Design1/countries.txt");


//    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        QTextStream in(&file);
//        QString line;

//        while(!in.atEnd())
//        {
//            line = in.readLine();
//            //            qDebug() << line ;
//            ui->countryComboBox->addItem(line);
//        }
//        in.flush();

//        file.close ();
//    }
//}

void GenCSR::addKeySizesItems()
{
    qDebug() << "Adding Key Sizes Items" ;
    ui->keySizesComboBox->setMaxVisibleItems(3);
    //  ui->keySizesComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //  ui->countryComboBox ->setEditable(true);

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

    //    name = ui->commonNameLineEdit->text();
    //    org = ui->organizationLineEdit->text();
    //    country = ui->countryComboBox->currentText();
    //    province = ui->provinceLineEdit->text();
    //    city = ui->cityLineEdit->text();

    keySize = ui->keySizesComboBox->currentText().toInt();

    //    qDebug()<< name;
    //    qDebug()<< org;
    //    qDebug()<< country;
    //    qDebug()<< province;
    //    qDebug()<< city;
    //    qDebug()<< keySize;

    std::string prvtKey = cert->generatePvtKey(keySize);
    std::cout << prvtKey <<std::endl;
    cert->generateCSR(384);
    std::cout << "\n\nCSR\n" << cert->getCertReq() << std::endl;

    if(cert->getCertReq()==std::string())
        std::cout << "CERTRequest true" <<std::endl;
    else
        std::cout << "CERTRequest false" <<std::endl;

    this->hide();

    QString CSR = QString::fromStdString(cert->getCertReq());


    Dialog *CSRdisplay = new Dialog(this,CSR);
    CSRdisplay->show();


    //    std::cout << "\n\nPUBLIC KEY FROM PRIVATE KEY\n" << cert->private2PublicKey();
    //    std::cout << "\n\nPUBLIC KEY FROM CERTIFICATE SIGNING REQUEST\n" << cert->CSR2PublicKey();
    //    std::cout << "\n\nCERTIFICATE SIGNING REQUEST DETAILS:\n" << cert->displayCSR();


    //GenCSR function

    //if GenCSR successful then
    //Message success
    // this->close();
    //QDialog displayCSR =  new QDial



    if(!conn.DBConnOpen())
    {
        qDebug() << "Failed to open DB";
        return;
    }

    conn.DBConnOpen();

    //Write to Database
    //        QSqlQuery qry;
    //        qry.prepare("insert into genCSRTable (keySize) values('"+keySize+"')");
    //             qry.prepare("insert into genCSRTable (name,org,country,province,city,keySize) "
    //                         "values ('"+name+"','"+org+"','"+country+"','"+province+"','"+city+"','"+keySize+"' ) ");

    //        if(qry.exec())
    //        {
    //            QMessageBox::critical(this,tr("Save"), tr("Saved"));
    //            conn.DBConnClose();
    //        }

    //        else
    //        {
    //            QMessageBox::critical(this,tr("error::"), qry.lastError().text());
    //        }

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
