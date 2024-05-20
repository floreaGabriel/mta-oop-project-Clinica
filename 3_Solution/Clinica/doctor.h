#ifndef DOCTOR_H
#define DOCTOR_H

#include "iuser.h"
#include <QDialog>


class Doctor : public IUser
{
private:
    std::string username;
    std::string nume;
    std::string prenume;
    std::string email;
    std::string parola;
    std::string phoneNumer;
    std::string CNP;
    std::string specializare;
public:
    Doctor();
    Doctor(std::string cpy_username,std::string cpy_nume,std::string cpy_prenume,
            std::string cpy_email, std::string cpy_parola,
            std::string cpy_phoneNumber,std::string cpy_CNP,
            std::string cpy_specializare);

    std::string getUsername() override { return this->username;};
    std::string getNume() override { return this->nume;};
    std::string getPrenume() override { return this->prenume;};
    std::string getEmail() override { return this->email;};
    std::string getParola() override { return this->parola;};
    std::string getPhonenumber() override { return this->phoneNumer;};
    std::string getCNP() override { return this->CNP;};
    std::string getSpecializare() override { return this->specializare;};
};

#endif // DOCTOR_H
