#include "export.h"
#include "ui_export.h"

Export::Export(QWidget *parent, int num) :
    QDialog(parent),
    ui(new Ui::Export)
{
    ui->setupUi(this);
    ui->label->setText(QString::number(num));
}

Export::~Export()
{
    delete ui;
}
