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
    //Inventory inventory; // We will use a shared pointer to manage the inventory, allowing for better memory management and flexibility in sharing the inventory across different parts of the system.
    std::shared_ptr<Inventory> inventory; 
    OrderProcessor * orderProcessor; 
    int warehouseID; 
    //std::string location; not needed for now 
public:
    Warehouse(int id , std::shared_ptr<Inventory> inv , OrderProcessor* processor) ;

    //main method to process orders + threads
    void process(); 
    
    // getters
    std::shared_ptr<Inventory> getInventory();
    OrderProcessor* getOrderProcessor();




    //std::string getLocation();
    
    // setters some  this are not needed for warehouse 
    //void setInventory(std::shared_ptr<Inventory> inventory); we dont need this because we will initialize the inventory in the constructor of the warehouse and we will not change it later on, so we can just use the constructor to set the inventory and we dont need a setter for it.
    //void setOrderProcessor(std::shared_ptr<OrderProcessor> processor);
    //void setLocation(std::string location);
    
    ~Warehouse();

};

#endif // WAREHOUSE_H
