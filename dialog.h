#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr, QString CSR = "");
    ~Dialog();

private slots:
    void on_copyCSR_Btn_3_clicked();

    void on_closeCSR_Btn_3_clicked();

    void on_saveCSR_Btn_3_clicked();

private:
    Ui::Dialog *ui;
    QString _CSR;
};

#endif // DIALOG_H
