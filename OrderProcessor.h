#ifndef ORDERPROCESSOR_H
#define ORDERPROCESSOR_H

#include <queue>
#include <memory>
#include <atomic>
#include <shared_mutex>
#include "Order.h"

class Inventory; // Forward declaration

class OrderProcessor
{
public:
    OrderProcessor();
    ~OrderProcessor();

    OrderProcessor(const OrderProcessor&) = delete;
    OrderProcessor& operator=(const OrderProcessor&) = delete;
    // Processing functions
    void processNextOrder();
    void startConcurrentProcessing();

    // Queue helpers
    bool isQueueEmpty();
    int getQueueSize();

    // Processed count
    int getProcessedCount();

    // Setters
    void setInventory(std::shared_ptr<Inventory> inv);

    // Order management
    //void addOrder(const Order& order);

private:
    std::shared_ptr<Inventory> inventory;
    std::atomic<int> processedCount{0};
    mutable std::shared_mutex queueMutex;
    std::queue<Order> pendingOrders;
};

#endif // ORDERPROCESSOR_H
