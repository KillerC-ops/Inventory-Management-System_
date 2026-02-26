#include "Order.h"

Order::Order(int orderID)
{
    //ctor
    orderID = orderID;
    orderStatus = 0;
    totalAmount = 0.0;
}

Order::~Order()
{
    //dtor
}

double Order::getTotalAmount() const {
    return totalAmount;
}


int Order::getStatus() const {
    return orderStatus; //0 for pending, 1 for success and 2 for failure
}


int Order::getOrderStatus() const {
    return orderStatus;
}

std::vector<std::shared_ptr<Product>> Order::getOrderProducts() const {
    return orderProducts;
}

void Order::addProduct(std::shared_ptr<Product> product) {

}

double Order::calculateTotal() {
    totalAmount = 0.0;

    return totalAmount;
}
