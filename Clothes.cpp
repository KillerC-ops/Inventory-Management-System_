#include "Clothes.h"

Clothes::Clothes(int productID, std::string name, double price, int quantity, int clothesID): Product(productID, name, price, quantity)

{
    //ctor
    clothesID = clothesID;
}

//Changed Clothes ->Muss

Clothes::~Clothes()
{
    //Distructor
}
// getter
int Clothes::getClothesID() {
    return clothesID;
}

double Clothes::calculateFinalPrice() {
    double price = getPrice();
    double tax = price * 0.15;  // 15% tax for clothes
    return price + tax;
}
