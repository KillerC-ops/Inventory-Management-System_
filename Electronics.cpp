#include "Electronics.h"

Electronics::Electronics(int productID, std::string name, double price, int quantity, int electronicID): Product(productID, name, price, quantity)
{
    //ctor
    electronicID = electronicID;
}

Electronics::~Electronics()
{
    //dtor
}
int Electronics::getElectronicID() {
    return electronicID;
}


double Electronics::calculateFinalPrice() {
    double price = getPrice();
    double tax = price * 0.10;  // 10% tax for electronics
    return price + tax;
}
