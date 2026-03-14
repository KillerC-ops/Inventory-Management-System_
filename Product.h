#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <atomic>

class Product
{
public:
    Product(int productID, std::string name, double price, int quantity);
    virtual ~Product();

private:
    int productID;
    std::string name;
    double price;
    std::atomic<int> quantity;

public:
    int getID();
    std::string getName();
    double getPrice();
    int getQuantity();

    void setName(std::string);
    void setQuantity(int);
    void setPrice(double);

    void increaseQuantity(int);
    void decreaseQuantity(int);

    void display();  // Changed

    // Make abstract
    virtual double calculateTax() = 0;

    virtual double calculateFinalPrice() = 0;
};

#endif // PRODUCT_H
