#include "Product.h"
#include <iostream>
using namespace std;

Product::Product(int productID, string name, double price, int quantity)
{
    //ctor
    this->productID = productID;
    this->name = name;
    this->price = price;
    this->quantity = quantity;
}

Product::~Product()
{
   
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
    return quantity.load(); // Use atomic load to get the current quantity
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
