#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <memory>
#include <atomic>
#include <shared_mutex>
#include <unordered_map>
#include "Product.h"

class Inventory
{
public:
    Inventory();
    ~Inventory();

private:
    std::unordered_map<std::string, std::shared_ptr<Product>> products;
    //std::atomic<int> totalItems;
    std::shared_mutex inventoryMutex;

public:
    bool addProduct(std::shared_ptr<Product> product);
    bool removeProduct(int id);
    std::shared_ptr<Product> findProduct(int id);
    void displayAllProducts();
    void sortProductByPrice();
    void sortProductByQuantity();

    // Setters
    void setProducts(std::unordered_map<std::string, std::shared_ptr<Product>> newProducts);
    void setTotalItems(int value);

    // Getter
    std::unordered_map<std::string, std::shared_ptr<Product>> getProducts();
    int getTotalItems();
};

#endif // INVENTORY_H
