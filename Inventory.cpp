#include <iostream>
#include <algorithm>
#include <vector>
#include "Inventory.h"
#include "Order.h"
//#include "OrderProcessor.h"
//#include "Warehouse.h"
#include "Product.h"
//#include "Electronics.h"
//#include "Clothes.h"
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

    std::lock_guard<std::shared_mutex> lock(inventoryMutex); // Lock the inventory for writing

    int key = product->getID(); 

    //Do not be shocked by the auto, it is just a way to simplify the code and make it more readable. It automatically deduces the type of the variable based on the initializer. In this case, it deduces that item is an iterator for the unordered_map<int, shared_ptr<Product>>.
    auto item = products.find(key);
    if (item != products.end()) {
        // Product exists, add quantity from the new product
        int newQuantity = product->getQuantity();
        item->second->increaseQuantity(newQuantity);
    } else {
        // Insert new product
        products[key] = product;
    }
    // Update totalItems by adding the quantity of the added product
    int qtyToAdd = product->getQuantity();
    totalItems += qtyToAdd;
    return true;

}

bool Inventory::removeProduct(int id, int amountToRemove) {

    std::lock_guard<std::shared_mutex> lock(inventoryMutex); // Lock the inventory for writing

    //checking if product exists
    auto item = products.find(id);

    if (item != products.end()) {
        //  The product exists, we need to get its quantity before removing it or its quantity from the map
        int currentQty = item->second->getQuantity();

        if (currentQty > amountToRemove) {
            // If the current quantity is greater than the amount to remove, we can just decrease the quantity
            item->second->decreaseQuantity(amountToRemove);
        } else {
            // If the current quantity is less than or equal to the amount to remove, we will remove the product from the map
            products.erase(item);
        }

        // Update totalItems by subtracting the quantity of the removed product
        totalItems -= amountToRemove;

        return true;
    }

    return false;
}


std::shared_ptr<Product> Inventory::findProduct(int id)
{
    std::shared_lock<std::shared_mutex> lock(inventoryMutex); // Lock the inventory for reading


    if (products.find(id) == products.end()) {
        return nullptr; // not found
    }

    return products.find(id)->second; // found
}


void Inventory::displayAllProducts() {
    std::shared_lock<std::shared_mutex> lock(inventoryMutex); // Lock the inventory for reading

    if(products.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    // loop through the map
    for(const auto& pair : products) {
        pair.second->display();
        std::cout << "\n";
    }

    std::cout << "Total Items: " << totalItems.load() << "\n";
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




bool Inventory::processOrder(int productID, int quantity){
    std::lock_guard<std::shared_mutex> lock(inventoryMutex); // Lock the inventory for writing

    auto product = products.find(productID);
    if (product != products.end()) {
        if (product->second->getQuantity() >= quantity) {
            product->second->decreaseQuantity(quantity);
            totalItems -= quantity; // Update total items in inventory
            return true; // Order processed successfully
        } else {
            // std::cout << "Not enough stock for product ID " << productID << ". Available: " << product->second->getQuantity() << ", Requested: " << quantity << std::endl;
            return false; // Not enough stock
        }
    } else {
       // std::cout << "Product ID " << productID << " not found in inventory." << std::endl;
        return false; // Product not found
    }
}
