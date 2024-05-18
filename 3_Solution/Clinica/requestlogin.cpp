#include "requestlogin.h"



RequestLogin::RequestLogin() {}

RequestLogin::RequestLogin(QString cUser,QString cPass,bool cDoctor):
    user(cUser),pass(cPass),doctor(cDoctor)
{

}


void RequestLogin::requestSEND(){
    QByteArray byteUser = user.toUtf8();
    QByteArray bytePass = pass.toUtf8();

    const char* dataUser = byteUser.constData();
    const char* dataPass = bytePass.constData();

    char* buff = (char*)malloc(strlen(dataUser) + strlen(dataPass) + strlen("Login")+4);

    if(doctor==true)
    {
        strcpy(buff,"3");
    }
    else
        strcpy(buff,"2");

    strcat(buff,"#");
    strcat(buff,dataUser);
    strcat(buff,"#");
    strcat(buff,dataPass);




    if (ClientConnection::getInstance().sendData(buff)) {
        // Message sent successfully
        qDebug() << "Message sent: " << buff;
        // insertCreds()
    }
}
