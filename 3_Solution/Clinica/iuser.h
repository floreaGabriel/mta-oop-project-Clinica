#ifndef IUSER_H
#define IUSER_H

#pragma once
#include <string>
#include <iostream>



class IUser
{
private:


public:
    IUser();

    virtual std::string getUsername() =0;
    virtual  std::string getNume() =0;
    virtual std::string getPrenume() =0;
    virtual std::string getEmail() =0;
    virtual std::string getParola() =0;
    virtual std::string getPhonenumber() =0;
    virtual std::string getCNP() =0;
    virtual std::string getSpecializare() =0;

};

#endif // IUSER_H
