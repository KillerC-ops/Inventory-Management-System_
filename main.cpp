#include <iostream>
#include <memory>
#include <limits>
#include "Electronics.h"
#include "Clothes.h"
#include "OrderProcessor.h"
#include "Product.h"
#include "Warehouse.h"
#include "Order.h"
#include "Inventory.h"
#include "Logger.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//Functions declarations
void displayMenu();
void handleAddProduct(shared_ptr<Inventory> inventory);
void handleRemoveProduct(shared_ptr<Inventory> inventory);
void handleSearchProduct(shared_ptr<Inventory> inventory);
void handleSortProducts(shared_ptr<Inventory> inventory);
void handleProcessOrders(shared_ptr<Inventory> inventory);




int main()
{
    srand(time(0)); // Initialize random seed
    // Clear log file at start
    ofstream logFile("logs.txt", ios::trunc);
    logFile.close();

    writeLog("Starting Inventory Management System"); 

    auto inventory = make_shared<Inventory>();
   inventory->addProduct(make_shared<Electronics>(101, "Laptop", 12000, 5, "16GB RAM"));
    // Electronics
    inventory->addProduct(make_shared<Electronics>(1, "Laptop", 15000, 5, "16GB RAM"));
    inventory->addProduct(make_shared<Electronics>(2, "Phone", 8000, 3, "128GB"));
    inventory->addProduct(make_shared<Electronics>(3, "Tablet", 6000, 2, "64GB"));
    inventory->addProduct(make_shared<Electronics>(4, "Monitor", 4000, 4, "24 inch"));
    inventory->addProduct(make_shared<Electronics>(5, "Keyboard", 500, 10, "Mechanical"));

    // Clothes
    inventory->addProduct(make_shared<Clothes>(6, "T-Shirt", 300, 8, "M", "Cotton"));
    inventory->addProduct(make_shared<Clothes>(7, "Jeans", 700, 5, "L", "Denim"));
    inventory->addProduct(make_shared<Clothes>(8, "Jacket", 1200, 2, "XL", "Leather"));
    inventory->addProduct(make_shared<Clothes>(9, "Shoes", 900, 6, "42", "Leather"));
    inventory->addProduct(make_shared<Clothes>(10, "Cap", 150, 12, "One Size", "Polyester"));

    // More mixed
    inventory->addProduct(make_shared<Electronics>(11, "Mouse", 250, 15, "Wireless"));
    inventory->addProduct(make_shared<Electronics>(12, "Speaker", 1200, 3, "Bluetooth"));
    inventory->addProduct(make_shared<Clothes>(13, "Hoodie", 800, 4, "L", "Fleece"));
    inventory->addProduct(make_shared<Clothes>(14, "Shorts", 400, 7, "M", "Cotton"));
    inventory->addProduct(make_shared<Electronics>(15, "Camera", 10000, 2, "HD"));


    int choice;  // Get user choice
    do {
        displayMenu();
        cin >> choice; // Get user choice

        switch (choice)
        {
        case 1: handleAddProduct(inventory); break;
        case 2: handleRemoveProduct(inventory); break;
        case 3: inventory->displayAllProducts(); break;
        case 4: handleSearchProduct(inventory); break;
        case 5: handleSortProducts(inventory); break;
        case 6: handleProcessOrders(inventory); break;
        case 7: cout << "Exiting system...\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 7);
   
    //Ignore the following line, it is just to pause the console so we can see the output before it closes
    std::cin.get();


  

    return 0;
}


void displayMenu()
{
    cout << "\n:::::::::::INVENTORY SYSTEM ::::::::::\n";
    cout << "1. Add Product\n";
    cout << "2. Remove Product\n";
    cout << "3. Display Products\n";
    cout << "4. Search Product\n";
    cout << "5. Sort Products\n";
    cout << "6. Process Orders (Threads)\n";
    cout << "7. Exit\n";
    cout << "Choose: ";
}



void handleAddProduct(shared_ptr<Inventory> inventory)
{
    int type;
    cout << "1. Electronics\n2. Clothing\nChoose type: ";
    cin >> type;

    int id, qty;
    double price;
    string name;

    cout << "Enter ID: "; 
    cin >> id;

    //Check if product ID already exists
    if (inventory->findProduct(id))
    {
        cout << "Product ID already exists! Try again.\n";
        return;
    }

    cout << "Enter Name: "; 
    cin >> name;
    cout << "Enter Price: "; 
    cin >> price;
    cout << "Enter Quantity: "; 
    cin >> qty;



    if (type == 1)
    {
        string specs;
        cout << "Enter Specs: ";
        cin.ignore();
        getline(cin, specs);

        inventory->addProduct(make_shared<Electronics>(id, name, price, qty, specs));
    }
    else
    {
        string size, material;
        cout << "Enter Size: "; cin >> size;
        cout << "Enter Material: "; cin >> material;

        inventory->addProduct(make_shared<Clothes>(id, name, price, qty, size, material));
    }

    cout << "Product added!\n";
}


void handleRemoveProduct(shared_ptr<Inventory> inventory)
{
    int id, qty;
    cout << "Enter Product ID: ";
    cin >> id;
    cout << "Enter Quantity to remove: ";
    cin >> qty;

    if (inventory->removeProduct(id, qty))
        cout << "Removed successfully\n";
    else
        cout << "Failed (check ID or quantity)\n";
}

void handleSearchProduct(shared_ptr<Inventory> inventory)
{
    int id;
    cout << "Enter Product ID: ";
    cin >> id;

    auto p = inventory->findProduct(id);

    if (p)
        p->display();
    else
        cout << "Product not found\n";
}

void handleSortProducts(shared_ptr<Inventory> inventory)
{
    int choice;
    cout << "1. Sort by Price\n2. Sort by Quantity\nChoose: ";
    cin >> choice;

    if (choice == 1)
    {
        auto sorted = inventory->sortProductsByPrice();
        for (auto& p : sorted)
            p->display();
    }
    else
    {
        auto sorted = inventory->sortProductsByQuantity();
        for (auto& p : sorted)
            p->display();
    }
}

void handleProcessOrders(shared_ptr<Inventory> inventory)
{
    OrderProcessor processor;
    processor.setInventory(inventory);

    cout << "\nProcessing orders using threads...\n";
    processor.processOrders();

    cout << "\n=== Orders ===\n";
    processor.displayOrders();

    cout<<endl;

    cout << "\n=== FINAL INVENTORY ===\n";
    inventory->displayAllProducts();
}