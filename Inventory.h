#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <memory>
#include <atomic>
#include <shared_mutex>
#include <unordered_map>
#include <vector>
#include "Product.h"
#include "Order.h"

class Inventory
{
public:
    Inventory();

private:
    std::unordered_map<int, std::shared_ptr<Product>> products;
    std::atomic<int> totalItems;
    std::shared_mutex inventoryMutex;

public:
    bool addProduct(std::shared_ptr<Product> product);
    bool removeProduct(int id, int amountToRemove);
    std::shared_ptr<Product> findProduct(int id);
    void displayAllProducts();
    std::vector<std::shared_ptr<Product>> sortProductsByPrice() const;
    std::vector<std::shared_ptr<Product>> sortProductsByQuantity() const;

    // Setters
    void setProducts(std::unordered_map<int, std::shared_ptr<Product>> newProducts);
    void setTotalItems(int value);

    // Getter
    std::unordered_map<int, std::shared_ptr<Product>> getProducts();
    int getTotalItems();
    std::vector<int> getAllProductIDs();

    //Process orders
    bool processOrder(int productID, int quantity);
};

#endif // INVENTORY_H
