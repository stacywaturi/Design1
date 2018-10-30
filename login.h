#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_signInBtn_clicked();

private:
    Ui::Login *ui;

    MainWindow *main = new MainWindow();
    std::string DB_TABLE3_NAME = "UsernameTable";
    std::string DB_TABLE3_COL_USERNAME = "Username";
    std::string DB_TABLE3_COL_PASSWORD = "Password";
    void createUsernameTable();

};

#endif // LOGIN_H
