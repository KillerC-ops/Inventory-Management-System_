#ifndef CLOTHES_H
#define CLOTHES_H

#include "Product.h"
#include <string>

class Clothes : public Product
{
public:
    Clothes(int productID, std::string name, double price, int quantity,
           int clothesID);

    ~Clothes() ;

private:
   int clothesID;

public:
    double calculateFinalPrice();
    int getClothesID();

};

#endif // CLOTHES_H
