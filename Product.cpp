#include "Product.h"
#include <iostream>
using namespace std;

Product::Product(int productID, string name, double price, int quantity)
{
    //ctor
    productID = productID;
    name = name;
    price = price;
    quantity = quantity;
}

Product::~Product()
{
    //dtor
}
//getters
int Product::getID() {
    return productID;
}

string Product::getName() {
    return name;
}

double Product::getPrice() {
    return price;
}

int Product::getQuantity() {
    return quantity;
}

//setters
void Product::setName(string newName) {
    name = newName;
}

void Product::setPrice(double newPrice) {
    price = newPrice;
}

void Product::setQuantity(int newQuantity) {
    quantity = newQuantity;
}


void Product::increaseQuantity(int amount) {
    quantity = quantity + amount;
}


void Product::decreaseQuantity(int amount) {
    quantity = quantity - amount;
}

void Product::display() {
    cout << "Product ID: " << productID << endl;
    cout << "Name: " << name << endl;
    cout << "Price: R" << price << endl;
    cout << "Quantity: " << quantity << endl;
}

double Product::calculateFinalPrice() {
    double tax = calculateTax();
    return price + tax;
}
