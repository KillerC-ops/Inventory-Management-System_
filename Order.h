#ifndef ORDER_H
#define ORDER_H

#include <atomic>
#include <vector>
#include <memory>
#include "Product.h"

class Order
{
public:
    Order(int orderID);
    ~Order();

    double getTotalAmount() const;
    int getStatus() const;
    int getOrderStatus() const;
    std::vector<std::shared_ptr<Product>> getOrderProducts() const;
    void addProduct(std::shared_ptr<Product> product);
    double calculateTotal();
private:
    int orderID;
    std::atomic<int> orderStatus{0};
    std::vector<std::shared_ptr<Product>> orderProducts;
    double totalAmount{0.0};

};

#endif // ORDER_H
