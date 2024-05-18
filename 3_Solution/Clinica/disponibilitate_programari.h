#ifndef DISPONIBILITATE_PROGRAMARI_H
#define DISPONIBILITATE_PROGRAMARI_H

#include<iostream>
#include<string.h>
#include<vector>



class Disponibilitate_Programari
{
private:
    std::string numeDoctor;
    std::string prenumeDoctor;
    std::string CNP;
    std::vector<std::string> intervale_orare;

public:
    Disponibilitate_Programari();
    Disponibilitate_Programari(std::string nume,std::string prenume,std::string cnp);
    void setNume(std::string nume) {this->numeDoctor=nume;};
    void setPrenume(std::string prenume) {this->prenumeDoctor=prenume;};
    void setCNP(std::string set_cnp) {this->CNP=set_cnp;};
    void setIntervalOcupat(int pozitie)
    {
        this->intervale_orare[pozitie] = "ocupat";
    }
    void add_interval(std::string text_interval) { this->intervale_orare.push_back((text_interval));};


    std::string getNume() { return this->numeDoctor;};
    std::string getPrenume() { return this->prenumeDoctor;};
    std::string getCNP () {return this->CNP;};
    std::vector<std::string> getIntervale_Vect() { return this->intervale_orare;};

};

#endif // DISPONIBILITATE_PROGRAMARI_H
