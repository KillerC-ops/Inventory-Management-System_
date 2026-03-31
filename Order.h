#ifndef ORDER_H
#define ORDER_H

#include <atomic>
#include <vector>
#include <memory>
#include "Product.h"


// what I commented out is not needed for order 
class Order
{
    private:
        int orderID;
        int productID; // This is the ID of the product being ordered
        int orderStatus ;
        int quantity;  

public:
    Order(int OrderID, int productID, int quantity);
    ~Order();

    //double getTotalAmount() const;
    int getOrderID() const;
    int getOrderStatus() const;
    int getProductID() const;
    int getQuantity() const;
    void setStatus(int status);    

};

#endif // ORDER_H
