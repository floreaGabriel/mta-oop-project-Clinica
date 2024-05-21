#include "login.h"
#include "ui_login.h"
#include"clientconnection.h"
#include"dashboard.h"
#include<string>

#include <QTimer>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->labelLoginEroare->hide();

    ui->radPacient->pressed();
    ui->radPacient->setChecked(1);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myFunction_timer()));


    setFixedSize(size());
}


void Login::myFunction_timer() {
    // Ascunde eticheta
    this->ui->labelLoginEroare->hide();
}


Login::~Login()
{
    delete ui;
}


void Login::setBackWindow(MainWindow* window)
{
    this->mainWindow=window;
}



void Login::on_pushButton_clicked()
{
    //back button

    this->close();
    this->mainWindow->show();

}


void Login::on_pushButton_2_clicked()
{
    //login button
    IRequest* req = new RequestLogin(ui->caseta_username->text(),
                                     ui->caseta_parola->text(),this->ui->radDoctor->isChecked());

    req->requestSEND();


    char responseBuffer[1024];
    if(ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer)))
    {
        qDebug() << "Mesaj primit: " << responseBuffer;
        if (responseBuffer[0] == '2') {
            qDebug() <<"Ai primit "<<responseBuffer<<"\n";

            std::vector<std::string> splitted_data_diez = CUtils::understandData(responseBuffer,'#');

            IUser* user;
            user = new Pacient(splitted_data_diez[1],splitted_data_diez[2],
                    splitted_data_diez[3],splitted_data_diez[4],splitted_data_diez[5],
                                   splitted_data_diez[6],splitted_data_diez[7]);

            this->mainWindow->hide();
            this->close();
            dashBoard* dashBoardWindow = new dashBoard(this,user);
            dashBoardWindow->setBackWindow(mainWindow);
            dashBoardWindow->show();

        }else if (responseBuffer[0] == '3'){
            qDebug() <<"Ai primit "<<responseBuffer<<"\n";

            std::vector<std::string> splitted_data_diez = CUtils::understandData(responseBuffer,'#');

            IUser* user;
            user = new Doctor(splitted_data_diez[1],splitted_data_diez[2],
                                  splitted_data_diez[3],splitted_data_diez[4],splitted_data_diez[5],
                                  splitted_data_diez[6],splitted_data_diez[7],splitted_data_diez[8]);


            this->mainWindow->hide();
            this->close();
            dashBoard* dashBoardWindow = new dashBoard(this,user);
            dashBoardWindow->setBackWindow(mainWindow);
            dashBoardWindow->show();
        }
        else if (strcmp(responseBuffer, "NOK") == 0) {
            qDebug() << "NUME SAU PAROLA NU SE POTRIVESC\n";
            this->ui->labelLoginEroare->setText("NUME SAU PAROLA NU COINCID");
            this->ui->labelLoginEroare->show();
            timer->start(5000);

        }
        else {
            // Handle error response from server
            qDebug() << "EROARE\n";

        }
    } else {
        // Handle receive error
    }

}


void Login::on_pushButton_3_clicked()
{
    if(this->ui->pushButton_3->text() == "⚠︎︎")
    {
        ui->caseta_parola->setEchoMode(QLineEdit::Password);
        this->ui->pushButton_3->setText("👁");
    } else if(this->ui->pushButton_3->text() == "👁")
    {
        ui->caseta_parola->setEchoMode(QLineEdit::Normal);
        this->ui->pushButton_3->setText("⚠︎︎");
    }
}

