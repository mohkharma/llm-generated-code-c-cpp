// Task182_Test.cpp
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

#include "../../../source/output/gpt4o/cpp/Task186_OPENAI_gpt-4o.cpp"

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

    ListNode* result = mergeKLists(lists);
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

    for (ListNode* l : lists) {
        deleteList(l);
    }
    deleteList(result);
}

int main() {
    runTest(1, {{1, 4, 5}, {1, 3, 4}, {2, 6}}, {1, 1, 2, 3, 4, 4, 5, 6});
    runTest(2, {}, {});
    runTest(3, {{}}, {});
    return 0;
}
