#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ClientConnection.h"
#include "signup.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::on_pushButton_clicked()
// {
//     //QString message = ui->lineEdit->text();
//     QByteArray byteArray = message.toUtf8();
//     const char * data =  byteArray.constData();

//     if (ClientConnection::getInstance().connectToServer("127.0.0.1", 12345)) {
//         // Connected successfully, send the message
//         if (ClientConnection::getInstance().sendData(data)) {
//             // Message sent successfully
//             qDebug() << "Message sent: " << message;
//         }
//     }
// }





// void MainWindow::on_SignUpButton_clicked()
// {

// }


void MainWindow::on_RegButton_clicked()
{
    if (ClientConnection::getInstance().connectToServer("127.0.0.1", 12345))
    {
        this->hide();
        SignUp* signupWindow = new SignUp();
        signupWindow->getMainWindow(this);
        signupWindow->show();
    }
}


void MainWindow::on_LogInButton_clicked()
{

}

