#include "OrderProcessor.h"
#include "Logger.h"
#include <iostream>
#include <thread>
using namespace std;

// Main method to process orders + threads 
void OrderProcessor::processOrders() {
    writeLog("starting order processing...");
    writeLog("Total orders to process: " + to_string(orders.size()));


    std::vector<std::thread> threads; // Vector to hold the threads for processing orders in parallel

    for (int i = 0; i < 20; i++)
    {
        Warehouse warehouse(i + 1, inventory, this); // Create a warehouse with a unique ID and the shared inventory and order processor
        threads.emplace_back(&Warehouse::process, warehouse); // Start a thread for each warehouse to process orders
        
    }
    for (auto& thread : threads) { 
        thread.join(); // Wait for all threads to finish processing 
    }

    writeLog("ending order processing...");
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

    if(orders.empty()) { // If there are no orders, we display a message and return
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
