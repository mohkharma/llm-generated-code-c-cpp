#include <string>
#include <unordered_set>

std::string longestDupSubstring(std::string s) {
    int n = s.length();
    int left = 1, right = n;
    std::string result = "";

    while (left <= right) {
        int mid = left + (right - left) / 2;
        std::unordered_set<std::string> seen;

        for (int i = 0; i <= n - mid; i++) {
            std::string sub = s.substr(i, mid);
            if (seen.find(sub) != seen.end()) {
                result = sub;
                left = mid + 1;
                break;
            }
            seen.insert(sub);
        }

        if (left > mid) {
            right = mid - 1;
        }
    }

    return result;
}
