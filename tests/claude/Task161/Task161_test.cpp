// Task_knapsack_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

// The C++ knapsack function from the user
int knapsack(int capacity, vector<int>& weights, vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                dp[i][w] = max(values[i-1] + dp[i-1][w-weights[i-1]], dp[i-1][w]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    return dp[n][capacity];
}

// Function to simulate the program behavior using stringstream for input/output
string runProgram(const string& input) {
    stringstream in(input);
    stringstream out;

    int capacity, n;
    out << "Enter knapsack capacity: ";
    in >> capacity;
    out << "Enter number of items: ";
    in >> n;

    vector<int> weights(n), values(n);

    out << "Enter weights of items: ";
    for (int i = 0; i < n; i++) {
        in >> weights[i];
    }

    out << "Enter values of items: ";
    for (int i = 0; i < n; i++) {
        in >> values[i];
    }

    int maxVal = knapsack(capacity, weights, values, n);
    out << "Maximum value: " << maxVal << "\n";

    return out.str();
}

// Test cases translated exactly from the Python testing logic
void test() {
    // Test case 1
    {
        string input = "50\n3\n10 20 30\n60 100 120\n";
        string expectedOutput =
            "Enter knapsack capacity: "
            "Enter number of items: "
            "Enter weights of items: "
            "Enter values of items: "
            "Maximum value: 220\n";
        string output = runProgram(input);
        assert(output == expectedOutput);
    }

    // Test case 2
    {
        string input = "0\n0\n\n\n";
        string expectedOutput =
            "Enter knapsack capacity: "
            "Enter number of items: "
            "Enter weights of items: "
            "Enter values of items: "
            "Maximum value: 0\n";
        string output = runProgram(input);
        assert(output == expectedOutput);
    }

    // Test case 3
    {
        string input = "10\n4\n5 4 6 3\n10 40 30 50\n";
        string expectedOutput =
            "Enter knapsack capacity: "
            "Enter number of items: "
            "Enter weights of items: "
            "Enter values of items: "
            "Maximum value: 90\n";
        string output = runProgram(input);
        assert(output == expectedOutput);
    }

    // Test case 4 - Edge case, capacity less than any item weight
    {
        string input = "2\n3\n3 4 5\n30 40 50\n";
        string expectedOutput =
            "Enter knapsack capacity: "
            "Enter number of items: "
            "Enter weights of items: "
            "Enter values of items: "
            "Maximum value: 0\n";
        string output = runProgram(input);
        assert(output == expectedOutput);
    }
}

int main() {
    test();
    cout << "All tests passed successfully.\n";
    return 0;
}
