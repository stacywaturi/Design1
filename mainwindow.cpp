#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gencsr.h"
#include "import.h"
#include "export.h"
#include "view.h"
#include "password.h"
#include "TFCertificate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/tfimage");
    ui->logo_label->setPixmap(pix);
    ui->logo_label->setScaledContents( true );

    ui->logo_label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored);

    ui->tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);



    createCertTable();
    getCertInfo();
    listCerts();

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->resizeColumnsToContents();

    //  ui->tableView->horizontalHeader()->setStretchLastSection(true);
    //  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::createCertTable(){

    DBConnOpen();

    QSqlQuery *qry = new QSqlQuery(mydb);
    qry->prepare("drop table "+ QString::fromStdString(DB_TABLE2_NAME));
    qry->exec();
    qry->prepare("create table "  + QString::fromStdString(DB_TABLE2_NAME) + "(  "  +
                 QString::fromStdString(DB_TABLE2_COL_NAME)+ " varchar(20) , " +
                 QString::fromStdString(DB_TABLE2_COL_EXPIRE)  + " varchar(20), "  +
                 QString::fromStdString(DB_TABLE2_COL_SERIAL)  + " varchar(20), "  +
                 QString::fromStdString(DB_TABLE2_COL_ISSUER) + " varchar(20))");
    qry->exec();
    DBConnClose();

}


void MainWindow::DBConnClose()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);

}

bool MainWindow::DBConnOpen()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QString::fromStdString(DB_FILE_NAME));

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
    newButtonPressed();
    DBConnOpen();

    GenCSR *genCSRObj;
    genCSRObj = new GenCSR(this);
    genCSRObj->setModal(true);
    genCSRObj->exec();

    DBConnClose();

    //Automatically Update Table of Certs
    on_refreshBtn_clicked();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::getCertInfo()
{
    std::string currentCert = "";
    DBConnOpen();
    QSqlQuery *query = new QSqlQuery(mydb);
    query->prepare("SELECT COUNT (*) FROM " + QString::fromStdString(DB_TABLE_NAME));
    query->exec();
    int rows =0;
    if(query->next())
        rows = query->value(0).toInt();

    //  qDebug() << "ROWS" << rows;

    for (int i = 1; i<rows+1;i++){
        TFCertificate *cert = new TFCertificate();
        if(cert->lookupDBCert(DB_FILE_NAME, DB_COL_ID, std::to_string(i))){

            string ccert = cert->getCert();

            QString qryString = "INSERT INTO  " +QString::fromStdString(DB_TABLE2_NAME) + " ("  +
                    QString::fromStdString(DB_TABLE2_COL_ISSUER) + ")"
                                                                   " SELECT " +  QString::fromStdString(DB_COL_ID) +
                    " FROM " + QString::fromStdString(DB_TABLE_NAME)  +
                    " WHERE " +  QString::fromStdString(DB_COL_CERT) + " IS NOT NULL";



            query->prepare("INSERT INTO  " +QString::fromStdString(DB_TABLE2_NAME) + " ("  +
                           QString::fromStdString(DB_TABLE2_COL_NAME) + ", " +
                           QString::fromStdString(DB_TABLE2_COL_EXPIRE)  + ", "  +
                           QString::fromStdString(DB_TABLE2_COL_SERIAL)  + ", "  +
                           QString::fromStdString(DB_TABLE2_COL_ISSUER) + ")"
                                                                          " VALUES (:" + QString::fromStdString(DB_TABLE2_COL_NAME) +
                           ", :" + QString::fromStdString(DB_TABLE2_COL_EXPIRE)+
                           ", :" + QString::fromStdString(DB_TABLE2_COL_SERIAL)+
                           ", :" + QString::fromStdString(DB_TABLE2_COL_ISSUER)+")");

            query->bindValue(":" + QString::fromStdString(DB_TABLE2_COL_NAME),  QString::fromStdString(cert->getInfo(INFO_SUBJECT_NAME)));

            if( QString::fromStdString (cert->getInfo(INFO_VALIDTO)).isEmpty())
                query->bindValue(":" + QString::fromStdString(DB_TABLE2_COL_EXPIRE), "Pending Certificate.. ");
            else
                query->bindValue(":" + QString::fromStdString(DB_TABLE2_COL_EXPIRE), QString::fromStdString (cert->getInfo(INFO_VALIDTO)));


            query->bindValue(":" + QString::fromStdString(DB_TABLE2_COL_SERIAL), QString::fromStdString(cert->getInfo(INFO_SERIAL)));
            query->bindValue(":" + QString::fromStdString(DB_TABLE2_COL_ISSUER),  QString::fromStdString(cert->getInfo(INFO_ISSUER_NAME)));
            query->exec();


        }
    }

    DBConnClose();
}



void MainWindow::on_refreshBtn_clicked()
{
    newButtonPressed();

    DBConnOpen();

    createCertTable();
    getCertInfo();
    listCerts();

    DBConnClose();


}
void MainWindow::listCerts()
{

    DBConnOpen();


    QSqlQuery *qry = new QSqlQuery(mydb);
    qry->prepare("select * from CertificateInfoTable");

    qry->exec();
    modal->setQuery(*qry);


    ui->tableView->setModel(modal);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(modal);

    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            SLOT(slotSelectionChange(const QItemSelection &, const QItemSelection &))
            );
    qDebug() << (modal->rowCount());

    DBConnClose();


}

void MainWindow::slotSelectionChange(const QItemSelection &, const QItemSelection &)
{


    ui->exportBtn->setEnabled(true);

    //QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();  //Here you are getting the indexes of the selected rows
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    QModelIndex index;

    QString text;
    foreach(index, indexes) {
        //text = QString("(%1)").arg(index.row());
        intIndx = index.row()+1;
        modal->setData(index, text);

    }

    qDebug() << intIndx;


}

void MainWindow::on_importBtn_clicked()
{


    DBConnOpen();

    Import *importObj= new Import(this);
    importObj->setModal(true);
    importObj->exec();

    DBConnClose();
    on_refreshBtn_clicked();

    //newButtonPressed();
}

void MainWindow::on_exportBtn_clicked()
{

    DBConnOpen();

    Export *exportObj = new Export(this,intIndx);
    if (exportObj->foundCertificate()){
        Password *pass = new Password(this);
        pass->setModal(true);
        pass->exec();
        //exportObj->setModal(true);
        //exportObj->exec();
    }
    DBConnClose();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &intIndx)
{
    DBConnOpen();

    View *viewObj = new View(this,(intIndx.row() +1));
    viewObj->setModal(true);
    //viewObj->exec();
    DBConnClose();

    qDebug() << "Viewing " << intIndx;
}

void MainWindow::newButtonPressed()
{
    ui->tableView->clearSelection();

    ui->exportBtn->setEnabled(false);


}
