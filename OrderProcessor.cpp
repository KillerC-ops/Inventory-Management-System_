#include "OrderProcessor.h"
#include <iostream>
#include <thread>
using namespace std;

//OrderProcessor::OrderProcessor()
//{
//    //ctor
//   processedCount = 0;
//    inventory = nullptr;
//}

//OrderProcessor::~OrderProcessor()
//{
//    //dtor
//}

// Main method to process orders + threads 

void OrderProcessor::processOrders() {
    std::vector<std::thread> threads;
    

    for (int i = 0; i < 5; i++)
    {
        Warehouse w(i + 1, inventory, this);
        threads.emplace_back(&Warehouse::process, w);
    }

    for (auto& thread : threads) {
        thread.join();
    }

//??
}
//void OrderProcessor::startConcurrentProcessing() {

//}
void OrderProcessor::setInventory(std::shared_ptr<Inventory> inv) {
    inventory = inv;
    cout << "Inventory connected to OrderProcessor" << endl;
}
int OrderProcessor::getProcessedCount() {
    return processedCount;
}

void OrderProcessor::displayOrders() {
    //std::shared_lock<std::mutex> lock(orderMutex); // Lock the orders for reading
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



//int OrderProcessor::getQueueSize() {
//    return pendingOrders.size();
//}
//bool OrderProcessor::isQueueEmpty() {
//    return pendingOrders.empty();
//}
