#define _CRT_SECURE_NO_WARNINGS
#include "signup.h"
#include "ui_signup.h"
#include "ClientConnection.h"
#include <string.h>


SignUp::SignUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_BackButton_clicked()
{
    this->close();
    mainWindow = new MainWindow();
    mainWindow->show();
}


void SignUp::on_SignUpButton_clicked()
{
    QString Nume = ui->lineedit_Nume->text();
    QString Prenume = ui->lineEdit_Prenume->text();
    QString Parola = ui->lineEdit_Parola->text();

    QByteArray byteNume = Nume.toUtf8();
    QByteArray bytePrenume = Prenume.toUtf8();
    QByteArray byteParola = Parola.toUtf8();

    const char * dataNume = byteNume.constData();
    const char * dataPrenume = bytePrenume.constData();
    const char * dataParola = byteParola.constData();

    char * data = (char*)malloc(strlen(dataNume) + strlen(dataPrenume) + strlen(dataParola) + 4);
    strcpy(data, "1");
    strcat(data, dataNume);
    strcat(data, "#");
    strcat(data, dataPrenume);
    strcat(data, "#");
    strcat(data, dataParola);

    if (ClientConnection::getInstance().sendData(data)) {
        // Message sent successfully
        qDebug() << "Message sent: " << data;
        // insertCreds()
    }

    this->hide();
    if(this->mainWindow == nullptr)
        this->mainWindow = new MainWindow();

    this->mainWindow->show();
}




