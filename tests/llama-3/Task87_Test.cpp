#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <string>

int binarySearch(int arr[], int target, int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

bool file_contains_valid_output(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string line;
    bool has_execution_time = false;
    bool has_target_info = false;
    while (std::getline(file, line)) {
        if (line.find("Execution time:") != std::string::npos) {
            has_execution_time = true;
        }
        if (line.find("Target found at index") != std::string::npos ||
            line.find("Target not found") != std::string::npos) {
            has_target_info = true;
        }
    }
    file.close();
    return has_execution_time && has_target_info;
}

int main() {
    int arr[10000];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 100);
    for (int i = 0; i < 10000; i++) {
        arr[i] = dis(gen);
    }
    std::sort(arr, arr + 10000);

    auto start_time = std::chrono::high_resolution_clock::now();
    int index = binarySearch(arr, 50, 0, 9999);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::string filename = "temp.txt";
    std::ofstream file(filename);
    double exec_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();
    file << "Execution time: " << exec_time << " seconds\n";
    if (index != -1) {
        file << "Target found at index " << index << "\n";
    } else {
        file << "Target not found\n";
    }
    file.close();

    bool pass = file_contains_valid_output(filename);

    if (pass) {
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
