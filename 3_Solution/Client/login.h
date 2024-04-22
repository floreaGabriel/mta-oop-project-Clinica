#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include"mainwindow.h"
namespace Ui {
class LogIn;
}

class LogIn : public QWidget
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

private slots:
    void on_LogInButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::LogIn *ui;
    MainWindow*main=nullptr;
};

#endif // LOGIN_H
