#include "requestregister.h"



RequestRegister::RequestRegister() {}

RequestRegister::RequestRegister(QString cuser, QString cpass1, QString cpass2, QString cFirstName, QString cLastName,
                                 QString cPhoneNumber, QString cEmail, QString cCNP, bool cdoctor, QString cSpecializare)
    :user(cuser),pass1(cpass1),pass2(cpass2),FirstName(cFirstName),LastName(cLastName),PhoneNumber(cPhoneNumber),
    Email(cEmail),CNP(cCNP),doctor(cdoctor),specializare(cSpecializare)
{

}


void RequestRegister::requestSEND()
{
    QByteArray byteUser = user.toUtf8();
    QByteArray bytePass = pass1.toUtf8();
    QByteArray byteFirstName = FirstName.toUtf8();
    QByteArray byteLastName = LastName.toUtf8();
    QByteArray bytePhoneNumber = PhoneNumber.toUtf8();
    QByteArray byteEmail = Email.toUtf8();
    QByteArray byteCNP = CNP.toUtf8();

    const char* dataUser = byteUser.constData();
    const char* dataPass = bytePass.constData();
    const char* dataFirstName = byteFirstName.constData();
    const char* dataLastName = byteLastName.constData();
    const char* dataPhoneNumber = bytePhoneNumber.constData();
    const char* dataEmail = byteEmail.constData();
    const char* dataCNP = byteCNP.constData();
    const char* dataSpecializare;
    if(doctor==true)
    {
        QByteArray byteSpecializare = specializare.toUtf8();
        dataSpecializare = byteSpecializare.constData();
    }

    char* buff;
    if(doctor==true)
    {
        buff = (char*) malloc (9+strlen(dataUser)+strlen(dataPass)+strlen(dataFirstName)
                               +strlen(dataLastName)+strlen(dataPhoneNumber)+
                               strlen(dataEmail)+strlen(dataCNP)+strlen(dataSpecializare));
    } else
        buff = (char*) malloc (9+strlen(dataUser)+strlen(dataPass)+strlen(dataFirstName)
                               +strlen(dataLastName)+strlen(dataPhoneNumber)+
                               strlen(dataEmail)+strlen(dataCNP));

    if(doctor==false)
        strcpy(buff,"0");
    else
        strcpy(buff,"1");

    strcat(buff,"#");
    strcat(buff,dataUser);
    strcat(buff,"#");
    strcat(buff,dataFirstName);
    strcat(buff,"#");
    strcat(buff,dataLastName);
    strcat(buff,"#");
    strcat(buff,dataEmail);
    strcat(buff,"#");
    strcat(buff,dataPass);
    strcat(buff,"#");
    strcat(buff,dataPhoneNumber);
    strcat(buff,"#");
    strcat(buff,dataCNP);

    if(doctor==true)
    {
        strcat(buff,"#");
        strcat(buff,dataSpecializare);
    }

    if (ClientConnection::getInstance().sendData(buff)) {
        // Message sent successfully
        qDebug() << "Message sent: " << buff;
        // insertCreds()
    }

    free(buff);
}

