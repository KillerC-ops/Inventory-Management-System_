#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include "Inventory.h"
#include "OrderProcessor.h"
#include <memory>

class Warehouse
{
public:
    Warehouse();
    ~Warehouse();

    // setters
    void setInventory(std::shared_ptr<Inventory> inventory);
    void setOrderProcessor(std::shared_ptr<OrderProcessor> processor);
    void setLocation(std::string location);

    // getters
    Inventory& getInventory();
    std::shared_ptr<OrderProcessor> getOrderProcessor();
    std::string getLocation();

private:
    Inventory inventory;
    std::shared_ptr<OrderProcessor> orderProcessor;
    std::string location;
};

#endif // WAREHOUSE_H
