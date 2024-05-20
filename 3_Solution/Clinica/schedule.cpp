#include "schedule.h"
#include "ui_schedule.h"
#include"home.h"
#include"account.h"
#include"search.h"
#include"shop.h"

#include"clientconnection.h"


Schedule::Schedule(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Schedule)
{
    ui->setupUi(this);

    ui->dataProgramare->setDisplayFormat("dd/MM/yyyy");

    ui->btnSearchDoctori->setIcon(QIcon("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/search-alb.png"));
    ui->comboSpecializare->addItem("Oftalmolog");
    ui->comboSpecializare->addItem("Dentist");
    ui->comboSpecializare->addItem("Cardiolog");
    ui->comboSpecializare->addItem("Hematolog");
    ui->comboSpecializare->addItem("Pediatru");
    ui->comboSpecializare->addItem("Psihiatru");
    ui->comboSpecializare->addItem("Ginecolog");
}

Schedule::~Schedule()
{
    delete ui;
}

void Schedule::on_btnHome_clicked()
{
    this->close();
    Home* homeWindow = new Home(this);
    homeWindow->show();
}


void Schedule::on_btnSchedule_clicked()
{
    this->close();
    Schedule* homeWindow = new Schedule(this);
    homeWindow->show();
}


void Schedule::on_btnShop_clicked()
{
    this->close();
    Shop* homeWindow = new Shop(this);
    homeWindow->show();
}


void Schedule::on_btnShop_2_clicked()
{
    this->close();
    Search* homeWindow = new Search(this);
    homeWindow->show();
}


void Schedule::on_btnAcoount_clicked()
{
    this->close();
    Account* homeWindow = new Account(this);
    homeWindow->show();
}


void Schedule::on_btnSearchDoctori_clicked()
{
    QString specializare,data;
    specializare = this->ui->comboSpecializare->currentText();
    data = this->ui->dataProgramare->text();

    QByteArray byteSpecializare = specializare.toUtf8();
    QByteArray byteData = data.toUtf8();

    const char* dataSpecializare = byteSpecializare.constData();
    const char* dataData = byteData.constData();

    char* buff = (char*) malloc(3 + sizeof(dataData) + sizeof(dataSpecializare));

    strcpy(buff,"4");
    strcat(buff,"#");
    strcat(buff,dataSpecializare);
    strcat(buff,"#");
    strcat(buff,dataData);


    if (ClientConnection::getInstance().sendData(buff)) {
        // Message sent successfully
        qDebug() << "Message sent: " << buff;
        // insertCreds()
    }





}























