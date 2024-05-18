#include "home.h"
#include "ui_home.h"
#include"account.h"
#include"schedule.h"
#include"search.h"
#include"shop.h"

Home::Home(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
}

Home::~Home()
{
    delete ui;
}

void Home::on_btnHome_clicked()
{
    this->close();
    Home* homeWindow = new Home(this);
    homeWindow->show();
}


void Home::on_btnSchedule_clicked()
{
    this->close();
    Schedule* homeWindow = new Schedule(this);
    homeWindow->show();
}


void Home::on_btnShop_clicked()
{
    this->close();
    Shop* homeWindow = new Shop(this);
    homeWindow->show();
}


void Home::on_btnShop_2_clicked()
{
    this->close();
    Search* homeWindow = new Search(this);
    homeWindow->show();
}


void Home::on_btnAcoount_clicked()
{
    this->close();
    Account* homeWindow = new Account(this);
    homeWindow->show();
}

