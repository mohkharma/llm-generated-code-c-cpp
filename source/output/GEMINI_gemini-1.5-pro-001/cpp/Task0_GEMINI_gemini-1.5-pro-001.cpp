#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <filesystem>

std::mutex file_mutex;

void process_file(const std::string& file_path) {
  // Acquire the mutex to ensure exclusive access to the file
  std::lock_guard<std::mutex> lock(file_mutex);

  // Open the file for reading
  std::ifstream file(file_path);

  // Check if the file is open
  if (file.is_open()) {
    // Process the file contents here
    std::string line;
    while (std::getline(file, line)) {
      // Example: print each line
      std::cout << line << std::endl;
    }

    // Close the file
    file.close();
  } else {
    std::cerr << "Error: Unable to open file: " << file_path << std::endl;
  }
}

int main() {
  // Directory containing the files to process
  std::string directory_path = "/path/to/directory";

  // Create a vector to store the threads
  std::vector<std::thread> threads;

  // Iterate over the files in the directory
  for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
    if (entry.is_regular_file()) {
      // Create a new thread to process the file
      threads.emplace_back(process_file, entry.path().string());
    }
  }

  // Join all the threads
  for (auto& thread : threads) {
    thread.join();
  }

  return 0;
}