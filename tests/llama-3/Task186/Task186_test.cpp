// Task182_Test.cpp
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

#include "../../../source/output/llama-3/cpp/Task186_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"
bool areEqual(ListNode* a, const std::vector<int>& expected) {
    for (int val : expected) {
        if (!a || a->val != val) return false;
        a = a->next;
    }
    return a == nullptr;
}

ListNode* buildList(const std::vector<int>& vals) {
    ListNode* dummy = new ListNode();
    ListNode* curr = dummy;
    for (int val : vals) {
        curr->next = new ListNode(val);
        curr = curr->next;
    }
    return dummy->next;
}

void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void runTest(int testNum, const std::vector<std::vector<int>>& inputLists, const std::vector<int>& expectedOutput) {
    std::vector<ListNode*> lists;
    for (const auto& sublist : inputLists) {
        lists.push_back(buildList(sublist));
    }

    Solution sol;
    ListNode* result = sol.mergeKLists(lists);
    if (areEqual(result, expectedOutput)) {
        std::cout << "✅ Test Case " << testNum << " Passed\n";
    } else {
        std::cout << "❌ Test Case " << testNum << " Failed\nExpected: ";
        for (int val : expectedOutput) std::cout << val << " ";
        std::cout << "\nGot: ";
        ListNode* temp = result;
        while (temp) {
            std::cout << temp->val << " ";
            temp = temp->next;
        }
        std::cout << "\n";
    }


    deleteList(result);
}

int main() {
    runTest(1, {{1, 4, 5}, {1, 3, 4}, {2, 6}}, {1, 1, 2, 3, 4, 4, 5, 6});
    runTest(2, {}, {});
    runTest(3, {{}}, {});
    return 0;
}
