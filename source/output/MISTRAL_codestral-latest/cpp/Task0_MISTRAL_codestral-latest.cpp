#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

std::mutex mtx;

void process_file(const std::string& filename) {
    mtx.lock();
    std::cout << "Processing file: " << filename << std::endl;
    // Add your file processing logic here
    mtx.unlock();
}

int main() {
    std::vector<std::thread> threads;
    for (const auto& entry : std::filesystem::directory_iterator("shared_directory")) {
        threads.push_back(std::thread(process_file, entry.path()));
    }
    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}