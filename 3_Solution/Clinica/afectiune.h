#ifndef AFECTIUNE_H
#define AFECTIUNE_H

#include<iostream>

class Afectiune
{
private:
    std::string nume;
    std::string CeEste;
    std::string cauze;
    std::string simptome;
    std::string medicamente;

public:
    Afectiune();
    Afectiune(std::string cpyNume,std::string cpyCeEste,std::string cpyCauze,std::string cpySimptome,std::string cpyMedicamente);

    void setNume(std::string cpy) {this->nume=cpy;}
    void setCeEste(std::string cpy) {this->CeEste=cpy;}
    void setCauze(std::string cpy) {this->cauze=cpy;}
    void setSimptome(std::string cpy) {this->simptome=cpy;}
    void setMedicament(std::string cpy) {this->medicamente=cpy;}
    std::string getNume() { return this->nume;}
    std::string getCeEste() { return this->CeEste;}
    std::string getCauze()  { return this->cauze;}
    std::string getSimptome() { return this->simptome;}
    std::string getMedicamente() { return this->medicamente;}

};

#endif // AFECTIUNE_H
