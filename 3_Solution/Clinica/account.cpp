#include "account.h"
#include "ui_account.h"
#include"home.h"
#include"schedule.h"
#include"search.h"
#include"shop.h"



Account::Account(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Account)
{
    ui->setupUi(this);
}

Account::~Account()
{
    delete ui;
}

void Account::on_btnHome_clicked()
{
    this->close();
    Home* homeWindow = new Home(this);
    homeWindow->show();
}


void Account::on_btnSchedule_clicked()
{
    this->close();
    Schedule* homeWindow = new Schedule(this);
    homeWindow->show();
}


void Account::on_btnShop_clicked()
{
    this->close();
    Shop* homeWindow = new Shop(this);
    homeWindow->show();
}


void Account::on_btnShop_2_clicked()
{
    this->close();
    Search* homeWindow = new Search(this);
    homeWindow->show();
}


void Account::on_btnAcoount_clicked()
{
    this->close();
    Account* homeWindow = new Account(this);
    homeWindow->show();
}

