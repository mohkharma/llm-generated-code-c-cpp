#include <stack>
#include <string>

class Solution {
public:
    int longestValidParentheses(std::string s) {
        int maxLen = 0;
        std::stack<int> st;
        st.push(-1); // Initialize with a sentinel
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i);
                } else {
                    maxLen = std::max(maxLen, i - st.top());
                }
            }
        }
        return maxLen;
    }
};
