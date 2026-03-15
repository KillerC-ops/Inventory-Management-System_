#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include <string>
#include "Product.h"

class Electronics : public Product
{
public:
    Electronics(int productID, std::string name, double price, int quantity, std::string specs);
    ~Electronics() ;

private:
    std::string specs;

public:
    std::string getSpecs();
    virtual double calculateTax() override;

};

#endif // ELECTRONICS_H
