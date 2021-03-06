#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    createUsernameTable();
    ui->result_label->setStyleSheet("QLabel {color : red; }");
}


void Login::createUsernameTable()
{


    main->DBConnOpen();

    QSqlQuery *qry = new QSqlQuery(main->mydb);
    // qry->prepare("drop table "+ QString::fromStdString(DB_TABLE3_NAME));
    qry->exec();
    qry->prepare("create table "  + QString::fromStdString(DB_TABLE3_NAME) + "(  "  +
                 QString::fromStdString(DB_TABLE3_COL_USERNAME)+ " varchar(20) , " +
                 QString::fromStdString(DB_TABLE3_COL_PASSWORD) + " varchar(20))");
    qry->exec();
    main->DBConnClose();
}



Login::~Login()
{
    delete ui;
}

void Login::on_signInBtn_clicked()
{
    qDebug() << "SIGN IN";
    QString username = ui->username_lineEdit->text();
    QString password = ui->password_lineEdit->text();

    main->DBConnOpen();
    QSqlQuery *query= new QSqlQuery(main->mydb);

    query->prepare("SELECT Username from UsernameTable WHERE Username = :username AND  Password = :password");
    query->bindValue(":username", username);
    query->bindValue(":password", password);

    if (query->exec())
    {
        if (query->next())
        {
            ui->result_label->setText("Valid Username and Password");
            QString msg = query->value(0).toString() +" is logged in";

            QMessageBox::warning(this, "Login", msg);

            this->close();
        }
        else
        {
            ui->result_label->setText("Login failed. Invalid username or password.");
        }
    }
    else
    {
        qDebug() << "Login failed. Query not executed.";
    }
    main->DBConnClose();

}
