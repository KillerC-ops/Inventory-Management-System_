#include "Logger.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <mutex>

using namespace std;

static mutex logMutex; // Allow only one thread at a time
void writeLog(const string& message)
{

    lock_guard<mutex> lock(logMutex);
    // Open file 
    ofstream logFile("logs.txt", ios::app);
    
    if (logFile.is_open()) {

        // Write message
        logFile << message << endl;
        
        // Close file
        logFile.close();
    }
}