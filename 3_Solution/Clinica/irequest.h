#ifndef IREQUEST_H
#define IREQUEST_H
#include"clientconnection.h"

class IRequest
{
public:
    IRequest();
    virtual void requestSEND()=0;
};

#endif // IREQUEST_H
