#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* createListNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* mergeKLists(struct ListNode** lists, int k) {
    if (k == 0) {
        return NULL;
    }
    struct ListNode* dummy = createListNode(0);
    struct ListNode* tail = dummy;
    while (1) {
        int minVal = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < k; i++) {
            if (lists[i] != NULL && lists[i]->val < minVal) {
                minVal = lists[i]->val;
                minIndex = i;
            }
        }
        if (minIndex == -1) {
            break;
        }
        tail->next = lists[minIndex];
        tail = tail->next;
        lists[minIndex] = lists[minIndex]->next;
    }
    return dummy->next;
}