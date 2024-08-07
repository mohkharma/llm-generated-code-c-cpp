#include <iostream>
#include <vector>
using namespace std;

//error: cannot bind non-const lvalue reference of type ‘std::vector<int>&’ to an rvalue of type ‘std::vector<int>’
// vector<int> twoSum(vector<int>& numbers, int target) {
vector<int> twoSum(const vector<int>& numbers, int target) {
    for (int i = 0; i < numbers.size(); i++) {
        for (int j = i + 1; j < numbers.size(); j++) {
            if (numbers[i] + numbers[j] == target) {
                return { i, j };
            }
        }
    }
    return {};
}

int main() {

    vector<int> result = twoSum({1, 2, 3}, 4);
    cout << "{" << result[0] << ", " << result[1] << "}" << endl;

    result = twoSum({3, 2, 4}, 6);
    cout << "{" << result[0] << ", " << result[1] << "}" << endl;

    return 0;
}