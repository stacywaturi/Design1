#ifndef IMPORT_H
#define IMPORT_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

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

private:
    Ui::Import *ui;
};

#endif // IMPORT_H
