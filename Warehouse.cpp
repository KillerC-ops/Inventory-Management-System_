#include "Warehouse.h"
#include <iostream>
#include <cstdlib>
#include "Logger.h"

using namespace std;

Warehouse::Warehouse( int id , std::shared_ptr<Inventory> inv , OrderProcessor* processor) 
{
    this->warehouseID = id;
    this->inventory = inv;
    this->orderProcessor = processor;
    
    writeLog("Warehouse " + to_string(warehouseID) + " created.");
}

std::shared_ptr<Inventory> Warehouse::getInventory()
{
    return inventory;
}

OrderProcessor* Warehouse::getOrderProcessor()
{
    return orderProcessor;
}

//Main method to process orders + threads
void Warehouse::process(){
    writeLog("Warehouse " + to_string(warehouseID) + " started working.");

    vector<int> productIDs = {1, 2, 3, 4, 5};

    int productID = productIDs[rand() % productIDs.size()];
    int quantity = rand() % 3 + 1; // order 1–3 items
    int qty = rand() % 2 + 1;

    int orderID;

    {
        orderID = orderProcessor->getNextOrderID();
    }

    writeLog("WarehouseID:" + to_string(warehouseID) + " is processing Order " + to_string(orderID) + " ProductID: " + to_string(productID) + " quantity:" + to_string(qty));
    Order order(orderID, productID, qty);

    bool success = inventory->processOrder(productID, qty);

    if (success){
        order.setStatus(1);

        writeLog("WarehouseID:" + to_string(warehouseID) + " SUCCESS: Order " + to_string(orderID) +" ProductID:" + to_string(productID) + " quantity:" + to_string(qty));
    }
    else{
        order.setStatus(2);

        writeLog("WarehouseID:" + to_string(warehouseID) + " FAILED: Order " + to_string(orderID) +  " ProductID:" + to_string(productID) + " quantity:" + to_string(qty) + " (not enough stock)");
    }

    {
        std::lock_guard<std::mutex> lock(orderProcessor->getOrderMutex());
        orderProcessor->getOrders().push_back(order);
    }

    std::cout << "Thread " << warehouseID
              << (success ? " SUCCESS " : " FAILED ")
              << " Product " << productID << std::endl;
       
}
