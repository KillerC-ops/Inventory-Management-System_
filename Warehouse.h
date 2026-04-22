#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include "Inventory.h"
#include "OrderProcessor.h"
#include <memory>

class OrderProcessor; // Forward declaration

class Warehouse
{

private:
    std::shared_ptr<Inventory> inventory; // Shared pointer to the inventory of the warehouse
    OrderProcessor * orderProcessor; // Pointer to the order processor that will handle orders for this warehouse
    int warehouseID; // Unique identifier for the warehouse
public:
    Warehouse(int id , std::shared_ptr<Inventory> inv , OrderProcessor* processor) ; //

    //main method to process orders + threads
    void process(); //
    
    // getters
    std::shared_ptr<Inventory> getInventory();
    OrderProcessor* getOrderProcessor(); 

};

#endif // WAREHOUSE_H
