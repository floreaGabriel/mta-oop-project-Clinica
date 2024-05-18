#include "afectiune.h"

Afectiune::Afectiune() {}

Afectiune::Afectiune(std::string cpyNume,std::string cpyCeEste,std::string cpyCauze,std::string cpySimptome,std::string cpyMedicamente)
    : nume(cpyNume),
    CeEste(cpyCeEste),cauze(cpyCauze),simptome(cpySimptome),medicamente(cpyMedicamente)
{}



