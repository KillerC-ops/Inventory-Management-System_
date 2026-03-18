#include <iostream>
#include <algorithm>
#include <vector>
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
    totalItems = 0;
}

Inventory::~Inventory()
{
    //dtor
}
bool Inventory::addProduct(shared_ptr<Product> product) {
    int key = product->getID(); 

    //Checking if product already exists
    if(products.find(key) != products.end()) {
        return false;
    }
    products[key] = product;
    return true;
}

bool Inventory::removeProduct(int id) {

    //checking if product exists
    if(products.erase(id) > 0) {
        return true;  // product successfully removed
    }

    return false; 
}


std::shared_ptr<Product> Inventory::findProduct(int id)
{
    if (products.find(id) == products.end()) {
        return nullptr; // not found
    }

    return products.find(id)->second; // found
}


void Inventory::displayAllProducts() {
    if(products.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    // loop through the map
    for(const auto& pair : products) {
        pair.second->display();
        std::cout << "\n";
    }
}


std::vector<std::shared_ptr<Product>> Inventory::sortProductsByPrice() const {
    // create a vector to hold the products
    std::vector<std::shared_ptr<Product>> sortedProducts;
    //  Copy all products from unordered_map to vector
    for (const auto& pair : products) {
        sortedProducts.push_back(pair.second);
    }

    // Sort the vector by final price (price + tax)
    // The lambda function compares the final price of two products
    std::sort(sortedProducts.begin(), sortedProducts.end(),
              [](const std::shared_ptr<Product>& a, const std::shared_ptr<Product>& b) {
                  return a->calculateFinalPrice() < b->calculateFinalPrice();
              });
    // Step 4: Return the sorted vector
    // The vector now has products from cheapest to most expensive (including tax)
    return sortedProducts;
}


/*void Inventory::sortProductsByQuantity(Order& order) const {
    // Step 1: Copy products from the unordered_map into a vector
    std::vector<std::shared_ptr<Product>> sortedProducts;
    for (const auto& pair : products) {
        sortedProducts.push_back(pair.second);
    }

    // Step 2: Sort the vector by quantity (ascending)
    std::sort(sortedProducts.begin(), sortedProducts.end(),
              [](const std::shared_ptr<Product>& a, const std::shared_ptr<Product>& b) {
                  return a->getQuantity() < b->getQuantity(); // uses atomic.load() internally
              });

    // Step 3: Add sorted products to the Order
    for (const auto& product : sortedProducts) {
        order.addProduct(product);
    }
}*/
std::vector<std::shared_ptr<Product>> Inventory::sortProductsByQuantity() const {
    // we create a temporary vector to store products
    std::vector<std::shared_ptr<Product>> sortedProducts;

    //adds the products from the unordered_map to the vector
    for (const auto& pair : products) {
        sortedProducts.push_back(pair.second);
    }

    // sort the vector by quantity in ascending order
    //the lambda function compares the quantity of two products
    std::sort(sortedProducts.begin(), sortedProducts.end(),
              [](const std::shared_ptr<Product>& a, const std::shared_ptr<Product>& b) {
                  return a->getQuantity() < b->getQuantity(); // Compare quantities
              });

    return sortedProducts;
}


// Setters
void Inventory::setProducts(unordered_map<int, shared_ptr<Product>> newProducts) {
    products = newProducts;
}

//void Inventory::setTotalItems(int value) {
//    totalItems = value;
//}

// Getters
unordered_map<int, shared_ptr<Product>> Inventory::getProducts() {
    return products;
}

//int Inventory::getTotalItems() {
   // return totalItems;
//}
