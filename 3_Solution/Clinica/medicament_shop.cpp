#include "medicament_shop.h"

Medicament_shop::Medicament_shop() {}


Medicament_shop::Medicament_shop(std::string name, std::string price, QPixmap photo)
    : nume(name),pret(price),poza(photo) {}
