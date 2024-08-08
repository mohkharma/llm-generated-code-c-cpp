#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <filesystem>
#include <future>

namespace fs = std::filesystem;

// Function to process a file
void processFile(const std::string& filePath, std::mutex& mutex, std::condition_variable& cv, std::unordered_map<std::string, std::future<void>>& processingFiles) {
    std::unique_lock<std::mutex> lock(mutex);
    // Wait for the file to be available
    while (processingFiles.find(filePath) != processingFiles.end()) {
        cv.wait(lock);
    }

    // Mark the file as being processed
    processingFiles[filePath] = std::async(std::launch::async, [] (const std::string& filePath) {
        // Actual file processing logic here
        std::cout << "Processing file: " << filePath << std::endl;
        // Simulate processing time
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }, filePath);

    lock.unlock();
    // Notify other threads that the file is being processed
    cv.notify_all();

    // Wait for the processing to finish
    processingFiles[filePath].get();
    processingFiles.erase(filePath);
}

int main1() {
    std::mutex mutex;
    std::condition_variable cv;
    std::unordered_map<std::string, std::future<void>> processingFiles;

    // Directory containing files
    const std::string directoryPath = "path/to/your/directory";

    std::vector<std::thread> threads;

    // Create threads to process files
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            threads.emplace_back(processFile, entry.path().string(), std::ref(mutex), std::ref(cv), std::ref(processingFiles));
        }
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
