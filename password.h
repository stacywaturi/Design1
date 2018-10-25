#ifndef PASSWORD_H
#define PASSWORD_H

#include <QDialog>

namespace Ui {
class Password;
}

class Password : public QDialog
{
    Q_OBJECT

public:
    explicit Password(QWidget *parent = nullptr, int num= 1);
    ~Password();

private slots:


    void on_OKBtn_clicked();

    void on_cancelBtn_clicked();



private:
    Ui::Password *ui;
    void checkPassword();
    QString _password = "1";
    int _num;
};

#endif // PASSWORD_H
