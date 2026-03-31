#include "Order.h"

Order::Order(int orderID , int productID, int quantity)
{
    //ctor
    this->orderID = orderID;
    this->productID = productID;
    this->quantity = quantity;
    this->orderStatus = 0;
    //totalAmount = 0.0;
}

int Order::getOrderID() const {
    return orderID;
}


int Order::getOrderStatus() const {
    return orderStatus;
}

int Order::getProductID() const {
    return productID;
}

int Order::getQuantity() const {
    return quantity;
}

void Order::setStatus(int status) {
    orderStatus = status;
}
