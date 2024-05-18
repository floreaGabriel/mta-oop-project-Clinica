#ifndef REQUESTLOGIN_H
#define REQUESTLOGIN_H

#include"irequest.h"
#include<QDialog>

class RequestLogin : public IRequest
{
private:
    QString user,pass;
    bool doctor;
public:
    RequestLogin();
    RequestLogin(QString cUser,QString cPass,bool cDoctor);
    void requestSEND() override;
};

#endif // REQUESTLOGIN_H
