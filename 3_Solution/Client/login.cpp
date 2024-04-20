#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LogIn)
{
    ui->setupUi(this);
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_LogInButton_clicked()
{



}


void LogIn::on_pushButton_clicked()
{
    this->close();
    this->main=new MainWindow();
    main->show();
}

