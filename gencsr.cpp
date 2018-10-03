#include "gencsr.h"
#include "ui_gencsr.h"

GenCSR::GenCSR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenCSR)
{
    ui->setupUi(this);

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
    MainWindow conn;
    QString name,org,country,province,city,keySize;

    //    name = ui->commonNameLineEdit->text();
    //    org = ui->organizationLineEdit->text();
    //    country = ui->countryComboBox->currentText();
    //    province = ui->provinceLineEdit->text();
    //    city = ui->cityLineEdit->text();
    keySize = ui->keySizesComboBox->currentText();

    //    qDebug()<< name;
    //    qDebug()<< org;
    //    qDebug()<< country;
    //    qDebug()<< province;
    //    qDebug()<< city;
    //    qDebug()<< keySize;

    if(!conn.DBConnOpen())
    {
        qDebug() << "Failed to open DB";
        return;
    }

    conn.DBConnOpen();

    //Write to Database
    QSqlQuery qry;
    qry.prepare("insert into genCSRTable (keySize) values('"+keySize+"')");
    //     qry.prepare("insert into genCSRTable (name,org,country,province,city,keySize) "
    //                 "values ('"+name+"','"+org+"','"+country+"','"+province+"','"+city+"','"+keySize+"' ) ");

    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Save"), tr("Saved"));
        conn.DBConnClose();
    }

    else
    {
        QMessageBox::critical(this,tr("error::"), qry.lastError().text());
    }

}

GenCSR::~GenCSR()
{
    delete ui;
}


void GenCSR::on_create_password_privatekey_radioButton_clicked()
{
    ui->hBoxCreatePassword->setEnabled(true);

}
