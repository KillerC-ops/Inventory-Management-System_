#ifndef ORDERPROCESSOR_H
#define ORDERPROCESSOR_H

#include <queue>
#include <memory>
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>
#include "Order.h"
#include "Warehouse.h"

class Inventory; // Forward declaration

class OrderProcessor
{
private:
    std::shared_ptr<Inventory> inventory;
    std::atomic<int> processedCount{0};
    std::mutex orderMutex;
    int nextOrderID = 1; // To generate unique order IDs

    std::vector<Order> orders; // Using vector instead of queue for better concurrent access
public:

    //Main method to process orders + threads
    void processOrders();


    void displayOrders(); // New method to display orders
    // Processed count
    int getProcessedCount();
    
    // Setters
    void setInventory(std::shared_ptr<Inventory> inv);

    std::mutex& getOrderMutex() {
        return orderMutex;
    }

    int getNextOrderID() {
        std::lock_guard<std::mutex> lock(orderMutex);
        return nextOrderID++;
    }

    std::vector<Order>& getOrders() {
        return orders;
    }
};

#endif // ORDERPROCESSOR_H
