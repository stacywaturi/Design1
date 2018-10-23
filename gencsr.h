#ifndef GENCSR_H
#define GENCSR_H

#include <QWidget>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QAction>
#include <QLineEdit>
#include <QToolButton>

#include "TFCertificate.h"
#include "mainwindow.h"

namespace Ui {
class GenCSR;
class Display;
}


class GenCSR : public QDialog
{
    Q_OBJECT

public:

    explicit GenCSR(QWidget *parent = nullptr);


    ~GenCSR();


    void gen_CSR();
private slots:
    //   void on_comboBox_clicked();

    void on_genCSRButton_clicked();
  //  void on_create_password_privatekey_radioButton_clicked();
  //  void on_createPassword_Btn_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::GenCSR *ui;
    QToolButton *button;
     QToolButton *button2;
     QIcon icon1, icon2;
    void addCountryItems();
    void addKeySizesItems();

    bool createPassword();
    bool enterPassword();
    void onPressed();
    void onReleased();
    void showPassword();
    void onPressed2();
    void onReleased2();
};

#endif // GENCSR_H
