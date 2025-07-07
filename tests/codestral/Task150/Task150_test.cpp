#include <iostream>
#include <cassert>

class SinglyLinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int data) : data(data), next(nullptr) {}
    };
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void insert(int data) {
        if (!head) {
            head = new Node(data);
        } else {
            Node* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = new Node(data);
        }
    }

    void deleteNode(int data) {
        if (!head) return;
        if (head->data == data) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            return;
        }
        Node* curr = head;
        while (curr->next) {
            if (curr->next->data == data) {
                Node* tmp = curr->next;
                curr->next = curr->next->next;
                delete tmp;
                return;
            }
            curr = curr->next;
        }
    }

    bool search(int data) {
        Node* curr = head;
        while (curr) {
            if (curr->data == data) return true;
            curr = curr->next;
        }
        return false;
    }

    Node* getHead() { return head; }
};

class TestSinglyLinkedList {
public:
    void run_tests() {
        test_insert();
        test_delete();
        test_delete_non_existent();
        test_delete_head();
        test_delete_last_element();
        test_search_found();
        test_search_not_found();
        test_insert_multiple();
        test_empty_list();
        test_search_empty_list();
        std::cout << "All test cases passed!" << std::endl;
    }

private:
    void test_insert() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        assert(sll.getHead() && sll.getHead()->data == 10);
        assert(sll.getHead()->next && sll.getHead()->next->data == 20);
    }

    void test_delete() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        sll.insert(30);
        sll.deleteNode(20);
        assert(sll.getHead() && sll.getHead()->data == 10);
        assert(sll.getHead()->next && sll.getHead()->next->data == 30);
    }

    void test_delete_non_existent() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        sll.deleteNode(40);
        assert(sll.getHead() && sll.getHead()->data == 10);
        assert(sll.getHead()->next && sll.getHead()->next->data == 20);
    }

    void test_delete_head() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        sll.deleteNode(10);
        assert(sll.getHead() && sll.getHead()->data == 20);
    }

    void test_delete_last_element() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        sll.deleteNode(20);
        assert(sll.getHead() && sll.getHead()->data == 10);
        assert(sll.getHead()->next == nullptr);
    }

    void test_search_found() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        assert(sll.search(20) == true);
    }

    void test_search_not_found() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        assert(sll.search(30) == false);
    }

    void test_insert_multiple() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        sll.insert(30);
        sll.insert(40);
        auto h = sll.getHead();
        assert(h && h->data == 10);
        assert(h->next && h->next->data == 20);
        assert(h->next->next && h->next->next->data == 30);
        assert(h->next->next->next && h->next->next->next->data == 40);
    }

    void test_empty_list() {
        SinglyLinkedList sll;
        assert(sll.getHead() == nullptr);
    }

    void test_search_empty_list() {
        SinglyLinkedList sll;
        assert(sll.search(10) == false);
    }
};

int main() {
    TestSinglyLinkedList tests;
    tests.run_tests();
    return 0;
}
