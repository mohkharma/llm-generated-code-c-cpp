#include <vector>
using namespace std;

bool xorGame(vector<int>& nums) {
    // "error: expected unqualified-id before ‘xor’ token. reserved keyword"
    int xor1 = 0;
    // int xor2 = 0;
    for (int num : nums) {
        xor1 ^= num;
    }
    return xor1 != 0 && nums.size() % 2 == 1;
}