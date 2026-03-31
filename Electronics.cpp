#include "Electronics.h"

Electronics::Electronics(int productID, std::string name, double price, int quantity, std::string specs): Product(productID, name, price, quantity)
{
    this->specs = specs;
}

Electronics::~Electronics()
{
  
}
std::string Electronics::getSpecs() {
    return specs;
}

double Electronics::calculateTax() {
    return getPrice() * 0.10;  // 10% tax for electronics
}
