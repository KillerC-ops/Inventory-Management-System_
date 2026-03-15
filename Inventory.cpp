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
    auto it = products.find(id);
    if (it != products.end()) {
        return it->second;
    }
    return nullptr;
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
    // Step 1: Create a temporary vector to store products
    // We use a vector because an unordered_map does not maintain any order
    std::vector<std::shared_ptr<Product>> sortedProducts;
    // Step 2: Copy all products from unordered_map to vector
    for (const auto& pair : products) {
        sortedProducts.push_back(pair.second);
    }

    // Step 3: Sort the vector by final price in ascending order
    // 'calculateFinalPrice()' includes the base price + tax
    // std::sort uses a lambda function to decide which product comes first
    // a < b means the product with smaller final price will appear first
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
    // Step 1: Create a vector to store products temporarily
    // We use a vector because unordered_map does not maintain any order
    std::vector<std::shared_ptr<Product>> sortedProducts;

    // Step 2: Copy all products from the unordered_map into the vector
    // 'products' is the unordered_map<int, shared_ptr<Product>>
    // 'pair.second' is the shared_ptr<Product>
    for (const auto& pair : products) {
        sortedProducts.push_back(pair.second);
    }

    // Step 3: Sort the vector by quantity in ascending order
    // std::sort takes a lambda function that tells it how to compare two products
    // a->getQuantity() < b->getQuantity() means smaller quantities come first
    std::sort(sortedProducts.begin(), sortedProducts.end(),
              [](const std::shared_ptr<Product>& a, const std::shared_ptr<Product>& b) {
                  return a->getQuantity() < b->getQuantity(); // Compare quantities
              });

    // Step 4: Return the sorted vector
    // Now the vector has the products sorted from lowest to highest quantity
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
