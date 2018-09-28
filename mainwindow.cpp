#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gencsr.h"
#include "import.h"
#include "export.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  DBConnOpen();



    if (!DBConnOpen())
    {
        ui->label2->setText("Failed to open DB");
    }
    else
        ui->label2->setText("Connected to DB");

    listCerts();

}

void MainWindow::DBConnClose()
{
    mydb.close();
    //    mydb.removeDatabase(QSqlDatabase::defaultConnection);

}

bool MainWindow::DBConnOpen()
{
    mydb= QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/sqlite3/certs.db");

    if (!mydb.open())
    {
        qDebug()<<("Failed to open DB");
        return false;
    }
    else
    {
        qDebug()<<("Connected to DB");
        return true;
    }


}
void MainWindow::on_genCSRBtn_clicked()
{
    DBConnClose();
    GenCSR *genCSRObj;

    genCSRObj = new GenCSR(this);
    genCSRObj->setModal(true);
    genCSRObj->exec();

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_refreshBtn_clicked()
{

}
void MainWindow::listCerts()
{

    DBConnOpen();

    QSqlQuery *qry = new QSqlQuery(mydb);
    qry->prepare("select * from Ceritficates");

    qry->exec();
    modal->setQuery(*qry);

    DBConnClose();
    ui->tableView->setModel(modal);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(modal);


    //    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    //    for( int i=0; i<selectedList.count(); i++)
    //            QMessageBox::information(this,tr(""), QString::number(selectedList.at(i).row()));



    //    connect(ui->tableView->selectionModel(),
    //            &QItemSelectionModel::currentRowChanged,
    //            ui->viewCertBtn,
    //            &QWidget::setEnabled);


    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            SLOT(slotSelectionChange(const QItemSelection &, const QItemSelection &))
            );
    qDebug() << (modal->rowCount());



}

void MainWindow::slotSelectionChange(const QItemSelection &, const QItemSelection &)
{
    ui->viewCertBtn->setEnabled(true);

    //   QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();//Here you are getting the indexes of the selected rows
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    QModelIndex index ;

    QString text;
    foreach(index, indexes) {
        //    text = QString("(%1)").arg(index.row());
        intIndx = index.row();
        modal->setData(index, text);

    }


    //qDebug() << text;
    qDebug() << intIndx;
    //QMessageBox::information(this,tr(""), (selection));
    //Now you can create your code using this information


}

void MainWindow::on_importBtn_clicked()
{

    DBConnClose();
    Import *importObj= new Import(this);
    importObj->setModal(true);
    importObj->exec();

}

void MainWindow::on_exportBtn_clicked()
{
    DBConnClose();
    Export *exportObj = new Export(this,9);
    exportObj->setModal(true);
    exportObj->exec();
}

void MainWindow::on_viewCertBtn_clicked()
{
    DBConnClose();
    Export *exportObj = new Export(this,intIndx);
    exportObj->setModal(true);
    exportObj->exec();
}
