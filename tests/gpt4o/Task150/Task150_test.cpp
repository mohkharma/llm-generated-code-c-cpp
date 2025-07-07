#include <iostream>
#include <cassert>

class Node {
public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void insert(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    bool deleteNode(int data) {
        Node* current = head;
        Node* prev = nullptr;
        while (current && current->data != data) {
            prev = current;
            current = current->next;
        }
        if (!current) {
            return false;
        }
        if (!prev) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        return true;
    }

    bool search(int data) {
        Node* current = head;
        while (current) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    Node* getHead() {
        return head;
    }
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
        sll.insert(1);
        sll.insert(2);
        assert(sll.getHead() && sll.getHead()->data == 1);
        assert(sll.getHead()->next && sll.getHead()->next->data == 2);
    }

    void test_delete() {
        SinglyLinkedList sll;
        sll.insert(1);
        sll.insert(2);
        sll.insert(3);
        sll.deleteNode(2);
        assert(sll.getHead() && sll.getHead()->data == 1);
        assert(sll.getHead()->next && sll.getHead()->next->data == 3);
    }

    void test_delete_non_existent() {
        SinglyLinkedList sll;
        sll.insert(1);
        sll.insert(2);
        bool result = sll.deleteNode(99);
        assert(result == false);
        assert(sll.getHead() && sll.getHead()->data == 1);
        assert(sll.getHead()->next && sll.getHead()->next->data == 2);
    }

    void test_delete_head() {
        SinglyLinkedList sll;
        sll.insert(1);
        sll.insert(2);
        bool result = sll.deleteNode(1);
        assert(result == true);
        assert(sll.getHead() && sll.getHead()->data == 2);
    }

    void test_delete_last_element() {
        SinglyLinkedList sll;
        sll.insert(1);
        sll.insert(2);
        bool result = sll.deleteNode(2);
        assert(result == true);
        assert(sll.getHead() && sll.getHead()->data == 1);
        assert(sll.getHead()->next == nullptr);
    }

    void test_search_found() {
        SinglyLinkedList sll;
        sll.insert(1);
        sll.insert(2);
        bool found = sll.search(2);
        assert(found == true);
    }

    void test_search_not_found() {
        SinglyLinkedList sll;
        sll.insert(1);
        sll.insert(2);
        bool found = sll.search(99);
        assert(found == false);
    }

    void test_insert_multiple() {
        SinglyLinkedList sll;
        sll.insert(1);
        sll.insert(2);
        sll.insert(3);
        sll.insert(4);
        Node* head = sll.getHead();
        assert(head && head->data == 1);
        assert(head->next && head->next->data == 2);
        assert(head->next->next && head->next->next->data == 3);
        assert(head->next->next->next && head->next->next->next->data == 4);
    }

    void test_empty_list() {
        SinglyLinkedList sll;
        assert(sll.getHead() == nullptr);
    }

    void test_search_empty_list() {
        SinglyLinkedList sll;
        bool found = sll.search(1);
        assert(found == false);
    }
};

int main() {
    TestSinglyLinkedList tests;
    tests.run_tests();
    return 0;
}
