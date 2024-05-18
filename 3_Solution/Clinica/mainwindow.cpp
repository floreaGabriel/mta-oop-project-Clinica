#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QPixmap>



#include "clientconnection.h"
#include "register.h"
#include "login.h"
#include<iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{ //25.20.193.54
    if (ClientConnection::getInstance().connectToServer("25.20.193.54",12345))
    {
    ui->setupUi(this);
    QPixmap pix("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/sigla-transparenta.png");
    ui->label_icon->setPixmap(pix.scaled(300,300,Qt::KeepAspectRatio));
    setFixedSize(size());
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //login
    this->hide();
    Login* loginWindow = new Login(this);
    loginWindow->setBackWindow(this);
    loginWindow->show();


}



void MainWindow::on_pushButton_2_clicked()
{
    //inregistrare

    this->hide();
    Register* registerWindow = new Register(this);
    registerWindow->setBackWindow(this);
    registerWindow->show();
}

