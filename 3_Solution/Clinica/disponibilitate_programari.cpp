#include "disponibilitate_programari.h"

Disponibilitate_Programari::Disponibilitate_Programari()
{
    for(int i=0;i<16;i++)
    {
        this->intervale_orare.push_back("NULL");
    }
}



Disponibilitate_Programari::Disponibilitate_Programari(std::string nume,std::string prenume,std::string cnp)
{
    this->numeDoctor=nume;
    this->prenumeDoctor=prenume;
    this->CNP=cnp;
    for(int i=0;i<16;i++)
    {
        this->intervale_orare.push_back("NULL");
    }
}
