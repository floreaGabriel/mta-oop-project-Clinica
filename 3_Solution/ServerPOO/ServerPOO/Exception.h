#pragma once
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

