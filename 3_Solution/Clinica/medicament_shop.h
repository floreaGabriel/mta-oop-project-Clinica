#ifndef MEDICAMENT_SHOP_H
#define MEDICAMENT_SHOP_H
#include<iostream>
#include <QLabel>

class Medicament_shop
{
private:
    std::string nume;
    std::string pret;
    //QLabel* poza;
    QPixmap poza;
public:
    Medicament_shop();
    Medicament_shop(std::string name, std::string price, QPixmap photo);
    std::string getPret() { return this->pret;};
    std::string returnNume() { return this->nume;};
    QPixmap returnPoza() { return this->poza;};
};

#endif // MEDICAMENT_SHOP_H
