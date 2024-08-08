#include <vector>
#include <algorithm>

using namespace std;

double findUniq(const vector<double>& arr) {
    vector<double> temp = arr; // Create a copy
    sort(temp.begin(), temp.end());
    return temp[0] == temp[1] ? temp[temp.size() - 1] : temp[0];
}
