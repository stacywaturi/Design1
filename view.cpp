#include "view.h"

View::View(QWidget *parent, int num):QDialog(parent)
{
    readSelected(num);
    this->setGeometry(23,45,21,44);
}

void View::readSelected(int &num){


    std::string id = "id_";
    std::string idValue = std::to_string(num);

    //    std::cout <<"Exporting" << cert->lookupDBCert(DB_FILE_NAME, id, idValue) <<std::endl;
    if( cert->lookupDBCert(DB_FILE_NAME, id, idValue)){
        if(QString::fromStdString(cert->getCert()).isEmpty()){
            QMessageBox::information(this,tr("Certificate"), "Could not find Certificate");
        }

        else
            writeToFile();
        //  ui->label->setText( QString::fromStdString( cert->displayCSR()));
    }



}
void View::writeToFile(){
    QString filename = "temp.crt";
    QFile file ( filename);

    if (file.open(QIODevice::WriteOnly)){
        QTextStream stream( &file );
        stream  << QString::fromStdString(cert->getCert());

    }


    QDesktopServices::openUrl(QUrl("temp.crt"));


}
