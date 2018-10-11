#ifndef IMPORT_H
#define IMPORT_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "TFCertificate.h"

#include "mainwindow.h"

namespace Ui {
class Import;
}

class Import : public QDialog
{
    Q_OBJECT

public:
    explicit Import(QWidget *parent = nullptr);
    ~Import();

private slots:
    void on_browseImport_Button_clicked();

    void on_okImport_Btn_clicked();

    void on_cancelImprt_Btn_clicked();

private:
    Ui::Import *ui;
TFCertificate  *cert = new TFCertificate();
};

#endif // IMPORT_H
