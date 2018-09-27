#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gencsr.h"
#include "import.h"


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
    QSqlQueryModel *modal = new QSqlQueryModel();
    DBConnOpen();

    QSqlQuery *qry = new QSqlQuery(mydb);
    qry->prepare("select * from Ceritficates");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QItemSelectionModel *select = ui->tableView->selectionModel();


    DBConnClose();
    qDebug() << (modal->rowCount());


}

void MainWindow::on_importBtn_clicked()
{
    DBConnClose();
    Import *importObj;

    importObj = new Import(this);
    importObj->setModal(true);
    importObj->exec();

}


