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
    thread_local std::mt19937 gen(std::random_device{}());  // Thread-local random number generator

    vector<int> productIDs = inventory->getAllProductIDs();  // Get all product IDs from the inventory
 
    if (productIDs.empty())
    {
        cout << "No products available\n";
        return;
    }

    std::uniform_int_distribution<> productDist(0, productIDs.size() - 1); // Distribution to select a random product ID from the list
    std::uniform_int_distribution<> quantityDist(1, 3); // Distribution to select a random quantity between 1 and 3 for the order

    
    int productID = productIDs[productDist(gen)]; // Select a random product ID from the list of available product IDs
    int quantity = quantityDist(gen);  // Select a random quantity for the order

    int orderID = orderProcessor->getNextOrderID();  

    writeLog("WarehouseID:" + to_string(warehouseID) + " is processing Order " + to_string(orderID) + " ProductID: " + to_string(productID) + " quantity:" + to_string(quantity));
    Order order(orderID, productID, quantity); // Create an order with the generated order ID, product ID, and quantity

    bool success = inventory->processOrder(productID, quantity); // Attempt to process the order in the inventory, which will return true if the order was successful (enough stock) or false if it failed (not enough stock or product not found)

    if (success){
        order.setStatus(1); // Set the order status to 1 for success

        writeLog("WarehouseID:" + to_string(warehouseID) + " SUCCESS: Order " + to_string(orderID) +" ProductID:" + to_string(productID) + " quantity:" + to_string(quantity));
    }
    else{
        order.setStatus(2);  // Set the order status to 2 for failure (not enough stock or product not found)

        writeLog("WarehouseID:" + to_string(warehouseID) + " FAILED: Order " + to_string(orderID) +  " ProductID:" + to_string(productID) + " quantity:" + to_string(quantity) + " (not enough stock)");
    }


    std::lock_guard<std::mutex> lock(orderProcessor->getOrderMutex());
    orderProcessor->getOrders().push_back(order); // Add the order to the order processor's list of orders, which is protected by a mutex to ensure thread safety when multiple warehouses are adding orders concurrently

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
