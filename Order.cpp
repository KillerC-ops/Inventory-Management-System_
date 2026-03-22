#include "Order.h"


//What I commented out is not needed for order
Order::Order(int orderID , int productID, int quantity)
{
    //ctor
    this->orderID = orderID;
    this->productID = productID;
    this->quantity = quantity;
    this->orderStatus = 0;
    //totalAmount = 0.0;
}

Order::~Order()
{
    //dtor
}

//double Order::getTotalAmount() const {
//    return totalAmount;
//}


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

//std::vector<std::shared_ptr<Product>> Order::getOrderProducts() const {
//    return orderProducts;
//}

//void Order::addProduct(std::shared_ptr<Product> product) {

//}

//double Order::calculateTotal() {
//    totalAmount = 0.0;

//    return totalAmount;
//}
