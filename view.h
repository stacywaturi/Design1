#ifndef VIEW_H
#define VIEW_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <TFCertificate.h>
#include <QMessageBox>

class View: public QDialog
{

public:
    explicit View(QWidget *parent = nullptr, int num= 0);

private:
    void readSelected(int &num);
    void writeToFile();
     TFCertificate *cert = new TFCertificate();
};

#endif // VIEW_H
