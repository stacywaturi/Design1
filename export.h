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
#include <QAction>
#include <QLineEdit>
#include <QToolButton>

namespace Ui {
class Export;
}

class Export : public QDialog
{
    Q_OBJECT

public:
    explicit Export(QWidget *parent = nullptr  ,int num= 1, TFCertificate *cert = nullptr);

    ~Export();

    bool foundCertificate();
private slots:
    void on_export_Button_clicked();
    void on_create_password_exportCert_radioButton_clicked();

    void on_browseExport_Button_clicked();
    void on_pushButton_2_clicked();



private:
    Ui::Export *ui;

    void readSelected(int &num);
    void writeToFile();
    void exportPfx();
     bool createPassword();

   TFCertificate *_cert;
    QString filename;
    int _num;
    QToolButton *button;
     QToolButton *button2;

     void showPassword();
     void onPressed();
     void onReleased();
};

#endif // EXPORT_H
