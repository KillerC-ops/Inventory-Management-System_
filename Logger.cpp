#include "Logger.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;

void writeLog(const string& message)
{
    // Open file 
    ofstream logFile("logs.txt", ios::app);
    
    if (logFile.is_open()) {

        // Write timestamp and message
        logFile << message << endl;
        
        // Close file
        logFile.close();
    }
}