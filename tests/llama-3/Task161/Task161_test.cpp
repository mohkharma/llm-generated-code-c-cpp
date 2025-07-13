// Task_knapsack_Test_Interactive.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int knapsack(int capacity, vector<int> weights, vector<int> values) {
    int n = (int)values.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

string runProgram(const string& input) {
    stringstream in(input);
    stringstream out;

    out << "Enter the capacity of the knapsack: ";
    int capacity; in >> capacity;

    out << "Enter the number of items: ";
    int n; in >> n;

    vector<int> weights(n);
    vector<int> values(n);

    for (int i = 0; i < n; i++) {
        out << "Enter the weight of item " << (i + 1) << ": ";
        in >> weights[i];
        out << "Enter the value of item " << (i + 1) << ": ";
        in >> values[i];
    }

    int maxValue = knapsack(capacity, weights, values);
    out << "Maximum value that can be put into the knapsack: " << maxValue << "\n";

    return out.str();
}

void test() {
    {
        string input =
            "50\n"
            "3\n"
            "10\n60\n"
            "20\n100\n"
            "30\n120\n";
        string expected =
            "Enter the capacity of the knapsack: "
            "Enter the number of items: "
            "Enter the weight of item 1: "
            "Enter the value of item 1: "
            "Enter the weight of item 2: "
            "Enter the value of item 2: "
            "Enter the weight of item 3: "
            "Enter the value of item 3: "
            "Maximum value that can be put into the knapsack: 220\n";
        assert(runProgram(input) == expected);
    }
    {
        string input =
            "0\n"
            "0\n";
        string expected =
            "Enter the capacity of the knapsack: "
            "Enter the number of items: "
            "Maximum value that can be put into the knapsack: 0\n";
        assert(runProgram(input) == expected);
    }
    {
        string input =
            "10\n"
            "4\n"
            "5\n10\n"
            "4\n40\n"
            "6\n30\n"
            "3\n50\n";
        string expected =
            "Enter the capacity of the knapsack: "
            "Enter the number of items: "
            "Enter the weight of item 1: "
            "Enter the value of item 1: "
            "Enter the weight of item 2: "
            "Enter the value of item 2: "
            "Enter the weight of item 3: "
            "Enter the value of item 3: "
            "Enter the weight of item 4: "
            "Enter the value of item 4: "
            "Maximum value that can be put into the knapsack: 90\n";
        assert(runProgram(input) == expected);
    }
    {
        string input =
            "2\n"
            "3\n"
            "3\n30\n"
            "4\n40\n"
            "5\n50\n";
        string expected =
            "Enter the capacity of the knapsack: "
            "Enter the number of items: "
            "Enter the weight of item 1: "
            "Enter the value of item 1: "
            "Enter the weight of item 2: "
            "Enter the value of item 2: "
            "Enter the weight of item 3: "
            "Enter the value of item 3: "
            "Maximum value that can be put into the knapsack: 0\n";
        assert(runProgram(input) == expected);
    }
}

int main() {
    test();
    cout << "All tests passed successfully.\n";
    return 0;
}
