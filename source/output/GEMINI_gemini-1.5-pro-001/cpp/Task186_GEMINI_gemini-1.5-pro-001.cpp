#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        priority_queue<ListNode*, vector<ListNode*>,
                       [](ListNode* a, ListNode* b) { return a->val > b->val; }> minHeap;
        for (ListNode* head : lists) {
            if (head != nullptr) {
                minHeap.push(head);
            }
        }
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (!minHeap.empty()) {
            ListNode* curr = minHeap.top();
            minHeap.pop();
            tail->next = curr;
            tail = tail->next;
            if (curr->next != nullptr) {
                minHeap.push(curr->next);
            }
        }
        return dummy.next;
    }
};