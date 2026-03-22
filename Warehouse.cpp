#include "Warehouse.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Warehouse::Warehouse( int id , std::shared_ptr<Inventory> inv , OrderProcessor* processor) 
{
    this->warehouseID = id;
    this->inventory = inv;
    this->orderProcessor = processor;

     //
    //ctor
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

    //int productID = rand() % 3 + 1;

    vector<int> productIDs = {1, 2, 3, 4, 5};

    int productID = productIDs[rand() % productIDs.size()];
    int quantity = rand() % 3 + 1; // order 1–3 items
    int qty = rand() % 2 + 1;

    int orderID;

    {
        //std::lock_guard<std::mutex> lock(orderProcessor->getOrderMutex());
        orderID = orderProcessor->getNextOrderID();
    }

    Order order(orderID, productID, qty);

    bool success = inventory->processOrder(productID, qty);

    if (success)
        order.setStatus(1);
    else
        order.setStatus(2);

    {
        std::lock_guard<std::mutex> lock(orderProcessor->getOrderMutex());
        orderProcessor->getOrders().push_back(order);
    }

    std::cout << "Thread " << warehouseID
              << (success ? " SUCCESS " : " FAILED ")
              << " Product " << productID << std::endl;
    
    
    
}

//setters:
//void Warehouse::setInventory(std::shared_ptr<Inventory> inventory) {
//    inventory = inventory;
//}
//void Warehouse::setOrderProcessor(std::shared_ptr<OrderProcessor> processor)
//{
//    orderProcessor = processor;
//}

//void Warehouse::setLocation(std::string loc)
//{
//    location = loc;
//}
//getters:

//std::string Warehouse::getLocation()
//{
    //    return location;
    //}
    
    Warehouse::~Warehouse()
    {
        //dtor
    }