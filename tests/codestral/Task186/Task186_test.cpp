// Task186_Test.cpp

#include <iostream>
#include <vector>
#include <cmath>
#include "../../../source/output/claude/cpp/Task186_CLAUDE_claude-3-5-sonnet-20240620.cpp"

std::vector<int> toVector(ListNode* head) {
    std::vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

ListNode* buildList(const std::vector<int>& vals) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

int main() {
    int passed = 0, total = 0;

    struct TestCase {
        std::vector<std::vector<int>> inputLists;
        std::vector<int> expectedOutput;
    };

    std::vector<TestCase> testCases = {
        {{{1, 4, 5}, {1, 3, 4}, {2, 6}}, {1, 1, 2, 3, 4, 4, 5, 6}},
        {{}, {}},
        {{{}}, {}},
        {{{-10, -5, 0}, {-2, 3}, {1}}, {-10, -5, -2, 0, 1, 3}},
        {{{1}}, {1}}
    };

    for (const auto& tc : testCases) {
        total++;

        // Build input list
        std::vector<ListNode*> listNodes;
        for (const auto& vec : tc.inputLists) {
            listNodes.push_back(buildList(vec));
        }

        // Run solution
        Solution sol;
        ListNode* result = sol.mergeKLists(listNodes);

        // Compare output
        std::vector<int> output = toVector(result);
        if (output == tc.expectedOutput) {
            std::cout << "Test Case " << total << " Passed.\n";
            passed++;
        } else {
            std::cout << "Test Case " << total << " Failed.\n";
            std::cout << "  Expected: ";
            for (int v : tc.expectedOutput) std::cout << v << " ";
            std::cout << "\n  Got:      ";
            for (int v : output) std::cout << v << " ";
            std::cout << "\n";
        }

        // Free only result list (no double-delete)
        while (result) {
            ListNode* tmp = result;
            result = result->next;
            delete tmp;
        }
    }

    std::cout << "\nTotal: " << passed << " / " << total << " test cases passed.\n";
    return 0;
}
