#include <string>
#include <vector>

using namespace std;
// updated by gimini
string foo(const vector<string>& strings) {
    string concatenatedString = "";
    for (const string& str : strings) {
        concatenatedString += str;
    }
    return concatenatedString;
}