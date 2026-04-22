#ifndef ORDER_H
#define ORDER_H

#include <atomic>
#include <vector>
#include <memory>
#include "Product.h"



class Order
{
    private:
        int orderID; // Unique identifier for the order
        int productID; // This is the ID of the product being ordered
        int orderStatus ;  // 1 = success, 2 = failed
        int quantity;  // Quantity of the product being ordered

public:
    Order(int OrderID, int productID, int quantity);
   

    //double getTotalAmount() const;
    int getOrderID() const;
    int getOrderStatus() const;
    int getProductID() const;
    int getQuantity() const;
    void setStatus(int status);    

};

#endif // ORDER_H
