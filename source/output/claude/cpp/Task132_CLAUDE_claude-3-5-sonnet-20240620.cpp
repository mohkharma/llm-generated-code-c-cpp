
#include <chrono>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>

void logEvent(const std::string& eventType, const std::string& description) {
    std::ofstream logFile("security_events.log", std::ios::app);
    if (logFile.is_open()) {
        //error: ‘std::chrono’ has not been declared.
        // fixed by including #include <chrono>
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        logFile << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") 
                << " - INFO - Event Type: " << eventType 
                << ", Description: " << description << std::endl;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file!" << std::endl;
    }
}
