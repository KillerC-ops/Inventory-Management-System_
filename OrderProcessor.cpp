#include "OrderProcessor.h"
#include <iostream>
using namespace std;

OrderProcessor::OrderProcessor()
{
    //ctor
    processedCount = 0;
    inventory = nullptr;
}

OrderProcessor::~OrderProcessor()
{
    //dtor
}
void OrderProcessor::processNextOrder() {
//??
}
void OrderProcessor::startConcurrentProcessing() {

}
void OrderProcessor::setInventory(std::shared_ptr<Inventory> inv) {
    inventory = inv;
    cout << "Inventory connected to OrderProcessor" << endl;
}
int OrderProcessor::getProcessedCount() {
    return processedCount;
}
int OrderProcessor::getQueueSize() {
    return pendingOrders.size();
}
bool OrderProcessor::isQueueEmpty() {
    return pendingOrders.empty();
}
