#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

class Exception
{
public:
    Exception(const std::string& message, int errorCode)
        : message(message), errorCode(errorCode) {}

    std::string getMessage() const {
        return message;
    }

    int getErrorCode() const {
        return errorCode;
    }

private:
    std::string message;
    int errorCode;
};




/*
    ------------- log errori --------------

    20 -> ServerConnection -> handleclient
    21 /
    22 /

    11 -> IRequest -> Factory



*/

#endif // EXCEPTION_H
