#include <stack>
#include <algorithm>
using namespace std;

int longestValidParentheses(string s) {
    stack<int> stk;
    stk.push(-1);
    int maxLength = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            stk.push(i);
        } else {
            stk.pop();
            if (!stk.empty()) {
                maxLength = max(maxLength, i - stk.top());
            } else {
                stk.push(i);
            }
        }
    }
    return maxLength;
}