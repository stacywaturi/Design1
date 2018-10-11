#ifndef EXPORT_H
#define EXPORT_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <TFCertificate.h>
#include <QtDebug>
#include <QMessageBox>

namespace Ui {
class Export;
}

class Export : public QDialog
{
    Q_OBJECT

public:
    explicit Export(QWidget *parent = nullptr, int num= 0);

    ~Export();

private slots:
    void on_export_Button_clicked();

    void on_create_password_exportCert_radioButton_clicked();

    void on_createPassword_Btn_3_clicked();

    void on_browseExport_Button_clicked();

private:
    Ui::Export *ui;

    void readSelected(int &num);
    void writeToFile();
    void exportPfx();

    TFCertificate *cert = new TFCertificate();
    QString filename;
    int _num;

};

#endif // EXPORT_H
