#include <iostream>
#include "Inventory.h"
#include "Order.h"
#include "OrderProcessor.h"
#include "Warehouse.h"
#include "Product.h"
#include "Electronics.h"
#include "Clothes.h"
using namespace std;

Inventory::Inventory()
{
    //ctor
    //totalItems = 0;
}

Inventory::~Inventory()
{
    //dtor
}
bool Inventory::addProduct(shared_ptr<Product> product) {

    return true;
}

bool Inventory::removeProduct(int id) {

    return false;
}


shared_ptr<Product> Inventory::findProduct(int id) {

    return nullptr;


}


void Inventory::displayAllProducts() {
    cout << "Total products: " << products.size() << endl;
}


void Inventory::sortProductByPrice() {

}


void Inventory::sortProductByQuantity() {

}

// Setters
void Inventory::setProducts(unordered_map<std::string, shared_ptr<Product>> newProducts) {

}

//void Inventory::setTotalItems(int value) {
//    totalItems = value;
//}

// Getters
unordered_map<std::string, shared_ptr<Product>> Inventory::getProducts() {
    return products;
}

//int Inventory::getTotalItems() {
   // return totalItems;
//}
