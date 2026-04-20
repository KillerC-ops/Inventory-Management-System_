#include "OrderProcessor.h"
#include "Logger.h"
#include <iostream>
#include <thread>
using namespace std;

// Main method to process orders + threads 
void OrderProcessor::processOrders() {
    writeLog("Starting order processing...");
    

    std::vector<std::thread> threads;

    for (int i = 0; i < 5; i++)
    {
        Warehouse warehouse(i + 1, inventory, this);
        threads.emplace_back(&Warehouse::process, warehouse);
        
    }
    for (auto& thread : threads) {
        thread.join();
    }

    writeLog("Ending order processing...");
    writeLog("Processed " + to_string(processedCount) + " out of " + to_string(orders.size()) + " orders.");
}
void OrderProcessor::setInventory(std::shared_ptr<Inventory> inv) {
    inventory = inv;
    cout << "Inventory connected to OrderProcessor" << endl;
}
int OrderProcessor::getProcessedCount() {
    return processedCount;
}

void OrderProcessor::displayOrders() {
    std::lock_guard<std::mutex> lock(orderMutex); // Lock the orders for reading

    if(orders.empty()) {
        std::cout << "No orders to display.\n";
        return;
    }

    for(const auto& order : orders) {
          std::cout << "Order " << order.getOrderID()
                  << " Product " << order.getProductID()
                  << " Qty " << order.getQuantity()
                  << " Status " << order.getOrderStatus()
                  << std::endl;
    }
}
