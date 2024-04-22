#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

    void getMainWindow(MainWindow* p) { mainWindow = p;}
private slots:
    void on_BackButton_clicked();

    void on_SignUpButton_clicked();

private:
    Ui::SignUp *ui;
    MainWindow* mainWindow = nullptr;
};

#endif // SIGNUP_H
