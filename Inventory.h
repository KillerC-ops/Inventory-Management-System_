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
    std::unordered_map<int, std::shared_ptr<Product>> products; // Map of product ID to Product object
    std::atomic<int> totalItems;                                // Total number of items in the inventory
    std::shared_mutex inventoryMutex;                           // Mutex for synchronizing access to the inventory    

public:
    bool addProduct(std::shared_ptr<Product> product); // Add a product to the inventory
    bool removeProduct(int id, int amountToRemove); // Remove a product from the inventory by its ID and the amount to remove
    std::shared_ptr<Product> findProduct(int id);  // Find a product in the inventory by its ID
    void displayAllProducts();                             // Display all products in the inventory
    std::vector<std::shared_ptr<Product>> sortProductsByPrice() const;  // Sort products by price in ascending order
    std::vector<std::shared_ptr<Product>> sortProductsByQuantity() const; // Sort products by quantity in ascending order

    // Setters
    void setProducts(std::unordered_map<int, std::shared_ptr<Product>> newProducts);
    void setTotalItems(int value);

    // Getter
    std::unordered_map<int, std::shared_ptr<Product>> getProducts();
    int getTotalItems(); // Get the total number of items in the inventory
    std::vector<int> getAllProductIDs(); // Get a vector of all product IDs in the inventory

    //Process orders
    bool processOrder(int productID, int quantity);  // Process an order by reducing the quantity of the specified product and updating total items in inventory
};

#endif // INVENTORY_H
