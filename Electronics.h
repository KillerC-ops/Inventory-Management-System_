#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include <string>
#include "Product.h"

class Electronics : public Product
{
public:
    Electronics(int productID, std::string name, double price, int quantity, int electronicID);
    ~Electronics() ;

private:
    int electronicID;

public:
    int getElectronicID();
    double calculateFinalPrice();

};

#endif // ELECTRONICS_H
