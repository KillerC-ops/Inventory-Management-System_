#include "Warehouse.h"
#include <iostream>
#include <cstdlib>
#include <random> // works better for Multithreading than cstdlib
#include <ctime>
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
    thread_local std::mt19937 gen(std::random_device{}());

    vector<int> productIDs = inventory->getAllProductIDs();

    if (productIDs.empty())
    {
        cout << "No products available\n";
        return;
    }

    std::uniform_int_distribution<> productDist(0, productIDs.size() - 1);
    std::uniform_int_distribution<> quantityDist(1, 3);

    
    int productID = productIDs[productDist(gen)];
    int quantity = quantityDist(gen);

    int orderID = orderProcessor->getNextOrderID();

    writeLog("WarehouseID:" + to_string(warehouseID) + " is processing Order " + to_string(orderID) + " ProductID: " + to_string(productID) + " quantity:" + to_string(quantity));
    Order order(orderID, productID, quantity);

    bool success = inventory->processOrder(productID, quantity);

    if (success){
        order.setStatus(1);

        writeLog("WarehouseID:" + to_string(warehouseID) + " SUCCESS: Order " + to_string(orderID) +" ProductID:" + to_string(productID) + " quantity:" + to_string(quantity));
    }
    else{
        order.setStatus(2);

        writeLog("WarehouseID:" + to_string(warehouseID) + " FAILED: Order " + to_string(orderID) +  " ProductID:" + to_string(productID) + " quantity:" + to_string(quantity) + " (not enough stock)");
    }

    {
        std::lock_guard<std::mutex> lock(orderProcessor->getOrderMutex());
        orderProcessor->getOrders().push_back(order);
    }

    std::string message;

    if (success)
    {
        message = "Thread " + to_string(warehouseID) +
                " SUCCESS Product " + to_string(productID);
    }
    else
    {
        message = "Thread " + to_string(warehouseID) +
                " FAILED Product " + to_string(productID);
    }

    
        
    cout << message << endl;
    
}
