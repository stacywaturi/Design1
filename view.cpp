#include "view.h"
#include "dialog.h"

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
            QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel {min-width:300px; font-size: 12px;}");
            msgBox.setText("This certificate is not available.");
            msgBox.setInformativeText("Do you want to view the Certificate Signing Request?");
            msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No );
            msgBox.setDefaultButton(QMessageBox::Yes);
            int ret = msgBox.exec();

            if(ret == QMessageBox::Yes)
            {
          //  QMessageBox::information(this,tr("Certificate"), "Certificate not available, \nPress OK to View/Save CSR");

            QString CSR = QString::fromStdString(cert->getCertReq());
            Dialog *CSRdisplay = new Dialog(this,CSR);
            CSRdisplay->show();
            }

            else {
                this->close();
            }
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


    QDesktopServices::openUrl(QUrl("temp.crt", QUrl::TolerantMode));


}

