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
    std::shared_ptr<Inventory> inventory; 
    OrderProcessor * orderProcessor; 
    int warehouseID; 
public:
    Warehouse(int id , std::shared_ptr<Inventory> inv , OrderProcessor* processor) ;

    //main method to process orders + threads
    void process(); 
    
    // getters
    std::shared_ptr<Inventory> getInventory();
    OrderProcessor* getOrderProcessor();

};

#endif // WAREHOUSE_H
