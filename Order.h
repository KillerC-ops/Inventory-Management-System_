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
        //std::atomic<int> orderStatus{0}; // 0 = pending, 1 = processed, 2 = failed
        int orderStatus ;
        //std::vector<std::shared_ptr<Product>> orderProducts;
        //std::atomic<int> quantity{0};
        int quantity;  
        //double totalAmount{0.0}; not needed

public:
    Order(int OrderID, int productID, int quantity);
    ~Order();

    //double getTotalAmount() const;
    int getOrderID() const;
    int getOrderStatus() const;
    int getProductID() const;
    int getQuantity() const;
    void setStatus(int status);
    //std::vector<std::shared_ptr<Product>> getOrderProducts() const;
    //void addProduct(std::shared_ptr<Product> product);
    //double calculateTotal();


    

};

#endif // ORDER_H
