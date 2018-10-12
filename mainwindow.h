#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

#include <QtWidgets>
#include <math.h>
#include "TFCertificate.h"





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Connect to Database
    QSqlDatabase mydb;
    void DBConnClose();
    bool DBConnOpen();

private slots:
    void on_genCSRBtn_clicked();
    void on_refreshBtn_clicked();
    void on_importBtn_clicked();
    void on_exportBtn_clicked();

    void slotSelectionChange(const QItemSelection &, const QItemSelection &);
    void on_viewCertBtn_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *modal = new QSqlQueryModel();
    //   TFCertificate *cert = new TFCertificate();
    int intIndx =0;
    std::string DB_TABLE2_NAME = "CertificateInfoTable";
    std::string DB_TABLE2_COL_ISSUER = "Issuer";
    std::string DB_TABLE2_COL_EXPIRE = "Expiry_Date";
    std::string DB_TABLE2_COL_SERIAL = "Serial_Number";
    std::string DB_TABLE2_COL_NAME = "Common_Name";

    void listCerts();
    void getCertInfo();
    void createCertTable();


};

#endif // MAINWINDOW_H
