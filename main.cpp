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
    // Starter products 5 electronics and 5 clothes
    inventory->addProduct(make_shared<Electronics>(101, "Laptop", 12000, 5, "16GB RAM"));
    inventory->addProduct(make_shared<Electronics>(102, "Smartphone", 8000, 10, "128GB Storage"));
    inventory->addProduct(make_shared<Electronics>(103, "Headphones", 1500, 2, "Noise Cancelling"));
    inventory->addProduct(make_shared<Electronics>(104, "Monitor", 3000, 4, "24 inch FHD"));
    inventory->addProduct(make_shared<Electronics>(105, "Keyboard", 700, 6, "Mechanical RGB"));

    inventory->addProduct(make_shared<Clothes>(201, "T-Shirt", 300, 10, "M", "Cotton"));
    inventory->addProduct(make_shared<Clothes>(202, "Jeans", 800, 5, "L", "Denim"));
    inventory->addProduct(make_shared<Clothes>(203, "Jacket", 1500, 2, "XL", "Leather"));
    inventory->addProduct(make_shared<Clothes>(204, "Sneakers", 1200, 3, "42", "Synthetic"));
    inventory->addProduct(make_shared<Clothes>(205, "Hoodie", 900, 1, "L", "Fleece"));

    int choice;

    do {
        displayMenu();
        cin >> choice;

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
}