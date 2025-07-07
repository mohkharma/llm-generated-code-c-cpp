// Task_knapsack_Test_Alt.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int knapsack(int capacity, vector<int> weights, vector<int> values, int n) {
    vector<vector<int>> K(n + 1, vector<int>(capacity + 1));
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (weights[i - 1] <= w)
                K[i][w] = max(values[i - 1] + K[i - 1][w - weights[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    return K[n][capacity];
}

string runProgram(const string& input) {
    stringstream in(input);
    stringstream out;

    out << "Enter knapsack capacity: ";
    int capacity; in >> capacity;

    out << "Enter number of items: ";
    int n; in >> n;

    vector<int> weights(n);
    vector<int> values(n);

    out << "Enter weights of items: ";
    for (int i = 0; i < n; i++) {
        in >> weights[i];
    }

    out << "Enter values of items: ";
    for (int i = 0; i < n; i++) {
        in >> values[i];
    }

    int max_value = knapsack(capacity, weights, values, n);
    out << max_value << "\n";

    return out.str();
}

void test() {
    {
        string input = "50\n3\n10 20 30\n60 100 120\n";
        string expected =
            "Enter knapsack capacity: "
            "Enter number of items: "
            "Enter weights of items: "
            "Enter values of items: "
            "220\n";
        assert(runProgram(input) == expected);
    }
    {
        string input = "0\n0\n\n\n";
        string expected =
            "Enter knapsack capacity: "
            "Enter number of items: "
            "Enter weights of items: "
            "Enter values of items: "
            "0\n";
        assert(runProgram(input) == expected);
    }
    {
        string input = "10\n4\n5 4 6 3\n10 40 30 50\n";
        string expected =
            "Enter knapsack capacity: "
            "Enter number of items: "
            "Enter weights of items: "
            "Enter values of items: "
            "90\n";
        assert(runProgram(input) == expected);
    }
    {
        string input = "2\n3\n3 4 5\n30 40 50\n";
        string expected =
            "Enter knapsack capacity: "
            "Enter number of items: "
            "Enter weights of items: "
            "Enter values of items: "
            "0\n";
        assert(runProgram(input) == expected);
    }
}

int main() {
    test();
    cout << "All tests passed successfully.\n";
    return 0;
}
