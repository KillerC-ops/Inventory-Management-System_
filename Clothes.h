#ifndef CLOTHES_H
#define CLOTHES_H

#include "Product.h"
#include <string>

class Clothes : public Product
{
public:
    Clothes(int productID, std::string name, double price, int quantity,
           std::string size, std::string material);

    ~Clothes() ;

private:
   std::string size;
   std::string material;

public:
    double calculateTax() override;
    std::string getSize();
    std::string getMaterial();

};

#endif // CLOTHES_H
