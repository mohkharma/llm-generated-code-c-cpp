// TaskXX_Test.cpp

#include <iostream>
#include <vector>
#include <sstream>
#include "../../../source/output/claude/cpp/Task186_CLAUDE_claude-3-5-sonnet-20240620.cpp"

void printList(ListNode* head) {
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << "->";
        head = head->next;
    }
    std::cout << "\n";
}

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

bool isEqual(ListNode* a, const std::vector<int>& expected) {
    ListNode* curr = a;
    for (int v : expected) {
        if (!curr || curr->val != v) return false;
        curr = curr->next;
    }
    return curr == nullptr;
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
        std::vector<ListNode*> listNodes;
        for (const auto& vec : tc.inputLists) {
            listNodes.push_back(buildList(vec));
        }

        Solution sol;
        ListNode* result = sol.mergeKLists(listNodes);
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

        // Cleanup memory
        while (result) {
            ListNode* tmp = result;
            result = result->next;
            delete tmp;
        }

    }

    std::cout << "\nTotal: " << passed << " / " << total << " test cases passed.\n";
    return 0;
}
