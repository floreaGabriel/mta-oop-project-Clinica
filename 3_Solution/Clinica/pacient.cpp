#include "pacient.h"

Pacient::Pacient() {}


Pacient::Pacient(std::string cpy_username,std::string cpy_nume,std::string cpy_prenume,
                 std::string cpy_email, std::string cpy_parola,
                 std::string cpy_phoneNumber,std::string cpy_CNP)
    :username(cpy_username),nume(cpy_nume),prenume(cpy_prenume),email(cpy_email), parola(cpy_parola),
    phoneNumer(cpy_phoneNumber), CNP(cpy_CNP)
{

}
