// Task_knapsack_Test_Recursive.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

// The recursive knapsack function you provided
int knapsack(int capacity, int weights[], int values[], int n) {
    if (n == 0 || capacity == 0)
        return 0;
    if (weights[n-1] > capacity)
        return knapsack(capacity, weights, values, n-1);
    else
        return max(values[n-1] + knapsack(capacity - weights[n-1], weights, values, n-1),
                   knapsack(capacity, weights, values, n-1));
}

// Function to simulate the program behavior with stringstream
string runProgram(const string& input) {
    stringstream in(input);
    stringstream out;

    int capacity, n;

    out << "Enter knapsack capacity: ";
    in >> capacity;

    out << "Enter number of items: ";
    in >> n;

    int weights[n];
    int values[n];

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

// Test cases same logic as before, adapted to this recursive version
void test() {
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
