#include <iostream>
#include <memory>
#include "Electronics.h"
#include "Clothes.h"
#include "OrderProcessor.h"
#include "Product.h"
#include "Warehouse.h"
#include "Order.h"
#include "Inventory.h"

using namespace std;

int main()
{
   // cout << "The System is in construction..." << endl;
    /*cout << "::::::::: Inventory Management System :::::::::::"<<endl;
    cout << "1. Add Product "<<endl;
    cout << "2. Remove Product "<<endl;
    cout << "3. Display All Products "<<endl;
    cout << "4. Search Product"<<endl;
    cout << "5. Sort Products"<<endl;
    cout << "6. Process Orders "<<endl;
    cout << "7. Exit "<<endl;
    cout << "Choose option: "<<endl;*/
    Inventory storeInventory;

    // Create some products
    auto laptop = std::make_shared<Electronics>(101, "Laptop", 1200.50, 10, "Intel i7, 16GB RAM");
    auto smartphone = std::make_shared<Electronics>(102, "Smartphone", 800.00, 25, "128GB Storage, 6GB RAM");
    auto tshirt = std::make_shared<Clothes>(201, "T-Shirt", 20.0, 50, "M", "Cotton");
    auto jeans = std::make_shared<Clothes>(202, "Jeans", 40.0, 30, "L", "Denim");
    auto laptop2 = std::make_shared<Electronics>(101, "Laptop", 1200.50, 50, "Intel i7, 16GB RAM");
    
    // Add products to inventory
    storeInventory.addProduct(laptop);
    storeInventory.addProduct(smartphone);
    storeInventory.addProduct(tshirt);
    storeInventory.addProduct(jeans);
    

    // Display all products
    std::cout << "=== Inventory List ===" << std::endl;
    storeInventory.displayAllProducts();

    storeInventory.addProduct(laptop2); // Adding the same laptop again to test quantity increase
    std::cout << "\n=== Inventory List After Adding Another Laptop ===" << std::endl;
    storeInventory.displayAllProducts();

    // Search for a product by ID
    int searchId = 102;
    std::cout << "\nSearching for product ID " << searchId << ":\n";
    auto found = storeInventory.findProduct(searchId);
    if (found) {
        found->display();
    } else {
        std::cout << "Product not found!" << std::endl;
    }

    // Remove a product
    int removeId = 102;
    std::cout << "\nRemoving product ID " << removeId << std::endl;
    if (storeInventory.removeProduct(removeId, 50)) {
        std::cout << "Product quantity removed successfully!" << std::endl;
    } else {
        std::cout << "Failed to remove product quantity." << std::endl;
    }

    // Display inventory after removal
    std::cout << "\n=== Updated Inventory ===" << std::endl;
    storeInventory.displayAllProducts();

    // Sort products by price
    auto sortedByPrice = storeInventory.sortProductsByPrice();
    std::cout << "\n=== Products Sorted by Final Price (Lowest First) ===" << std::endl;
    for (auto& p : sortedByPrice) {
        p->display();
        std::cout << "Final Price: R" << p->calculateFinalPrice() << std::endl << std::endl;
    }

    // Sort products by quantity
    auto sortedByQuantity = storeInventory.sortProductsByQuantity();
    std::cout << "\n=== Products Sorted by Quantity (Lowest First) ===" << std::endl;
    for (auto& p : sortedByQuantity) {
        p->display();
        std::cout << std::endl;
    }


    // Testing Process an order without threads for simplicity
   // int orderProductID = 104; // This product ID does not exist to test the failure case
    //int orderQuantity = 5;
    //std::cout << "\nProcessing order for product ID " << orderProductID << " with quantity " << orderQuantity << ":\n";
    //if (storeInventory.processOrder(orderProductID, orderQuantity)) {
    //    std::cout << "Order processed successfully!" << std::endl;
    //} else {
    //    std::cout << "Failed to process order. Not enough stock or product not found." << std::endl;
    //}





    cout << "\n=== TESTING THREADS ===\n";

    auto sharedInventory = make_shared<Inventory>();

    sharedInventory->addProduct(make_shared<Electronics>(1, "Laptop", 15000, 2, "16GB RAM"));
    sharedInventory->addProduct(make_shared<Electronics>(2, "Phone", 8000, 1, "128GB"));
    sharedInventory->addProduct(make_shared<Electronics>(3, "Headphones", 1500, 0, "NC")); // always fail
    sharedInventory->addProduct(make_shared<Clothes>(4, "T-Shirt", 300, 2, "M", "Cotton"));
    sharedInventory->addProduct(make_shared<Clothes>(5, "Jacket", 1200, 1, "L", "Leather"));

    OrderProcessor processor;
    processor.setInventory(sharedInventory);

    processor.processOrders(); // Process all orders concurrently

    
    cout << "\n=== ORDERS ===\n";
    processor.displayOrders();
    



    //Ignore the following line, it is just to pause the console so we can see the output before it closes
    std::cin.get();
    return 0;
}
