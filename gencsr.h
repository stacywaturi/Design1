#ifndef GENCSR_H
#define GENCSR_H

#include <QWidget>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>

#include "mainwindow.h"



namespace Ui {
class GenCSR;
}

class GenCSR : public QDialog
{
    Q_OBJECT

public:

    explicit GenCSR(QWidget *parent = nullptr);
    ~GenCSR();


private slots:
 //   void on_comboBox_clicked();

    void on_genCSRButton_clicked();

private:
    Ui::GenCSR *ui;
    void addCountryItems();
    void addKeySizesItems();
};

#endif // GENCSR_H
