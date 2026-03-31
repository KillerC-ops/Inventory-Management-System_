#include "Clothes.h"

Clothes::Clothes(int productID, std::string name, double price, int quantity, std::string size, std::string material): Product(productID, name, price, quantity)

{
    this->size = size;
    this->material = material;
}
Clothes::~Clothes()
{
   
}

// getter
std::string Clothes::getSize() {
    return size;
}

std::string Clothes::getMaterial() {
    return material;
}

double Clothes::calculateTax() {
    return getPrice() * 0.15;  // 15% tax for clothes
}
