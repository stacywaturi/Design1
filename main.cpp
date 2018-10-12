#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include "TFCertificate.h"

int		TF_CERT_ERROR_INDEX = TF_CERT_no_error;
string	LOG_FILE_CERTMNGR   = "cert_mngr.log" ;
string  DB_FILE_NAME        = "cert_mngr.db";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
