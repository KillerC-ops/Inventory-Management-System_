#include "Warehouse.h"
#include <iostream>
using namespace std;

Warehouse::Warehouse()
{
    //ctor
}

Warehouse::~Warehouse()
{
    //dtor
}
//setters:
void Warehouse::setInventory(std::shared_ptr<Inventory> inventory) {
    inventory = inventory;
}
void Warehouse::setOrderProcessor(std::shared_ptr<OrderProcessor> processor)
{
    orderProcessor = processor;
}

void Warehouse::setLocation(std::string loc)
{
    location = loc;
}
//getters:
Inventory& Warehouse::getInventory()
{
    return inventory;
}

std::shared_ptr<OrderProcessor> Warehouse::getOrderProcessor()
{
    return orderProcessor;
}

std::string Warehouse::getLocation()
{
    return location;
}
