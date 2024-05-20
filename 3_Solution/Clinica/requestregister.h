#ifndef REQUESTREGISTER_H
#define REQUESTREGISTER_H
#include <QDialog>

#include"irequest.h"



class RequestRegister : public IRequest
{
private:
    QString user,pass1,pass2,FirstName,LastName,PhoneNumber,Email,CNP;
    QString specializare;
    bool doctor;


public:
    RequestRegister();
    RequestRegister(QString cuser, QString cpass1, QString cpass2, QString cFirstName, QString cLastName, QString cPhoneNumber, QString cEmail, QString cCNP, bool cdoctor, QString cSpecializare);
    void requestSEND() override;

};

#endif // REQUESTREGISTER_H
