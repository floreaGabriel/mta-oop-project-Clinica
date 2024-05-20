#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"
#include"requestlogin.h"

using namespace std;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void setBackWindow(MainWindow* window);


private slots:
    void myFunction_timer();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Login *ui;
    MainWindow* mainWindow = nullptr;
    QTimer *timer;
};

#endif // LOGIN_H
