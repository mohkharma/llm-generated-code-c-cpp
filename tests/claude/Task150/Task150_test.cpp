#include <iostream>
#include <sstream>
#include <cassert>

class Node {
public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class SinglyLinkedList {
public:
    Node* head;

    SinglyLinkedList() : head(nullptr) {}

    void insert(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) current = current->next;
            current->next = newNode;
        }
    }

    void deleteNode(int data) {
        if (!head) return;
        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* current = head;
        while (current->next) {
            if (current->next->data == data) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }

    bool search(int data) {
        Node* current = head;
        while (current) {
            if (current->data == data) return true;
            current = current->next;
        }
        return false;
    }
};

class TestSinglyLinkedList {
public:
    TestSinglyLinkedList() {
        run_tests();
    }

    void test_insert() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        assert(sll.head != nullptr && sll.head->data == 10);
        assert(sll.head->next != nullptr && sll.head->next->data == 20);
    }

    void test_delete() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        sll.insert(30);
        sll.deleteNode(20);
        assert(sll.head != nullptr && sll.head->data == 10);
        assert(sll.head->next != nullptr && sll.head->next->data == 30);
    }

    void test_delete_non_existent() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        sll.deleteNode(40);
        assert(sll.head != nullptr && sll.head->data == 10);
        assert(sll.head->next != nullptr && sll.head->next->data == 20);
    }

    void test_delete_head() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        sll.deleteNode(10);
        assert(sll.head != nullptr && sll.head->data == 20);
    }

    void test_delete_last_element() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        sll.deleteNode(20);
        assert(sll.head != nullptr && sll.head->data == 10);
        assert(sll.head->next == nullptr);
    }

    void test_search_found() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        bool result = sll.search(20);
        assert(result == true);
    }

    void test_search_not_found() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        bool result = sll.search(30);
        assert(result == false);
    }

    void test_insert_multiple() {
        SinglyLinkedList sll;
        sll.insert(10);
        sll.insert(20);
        sll.insert(30);
        sll.insert(40);
        assert(sll.head != nullptr && sll.head->data == 10);
        assert(sll.head->next != nullptr && sll.head->next->data == 20);
        assert(sll.head->next->next != nullptr && sll.head->next->next->data == 30);
        assert(sll.head->next->next->next != nullptr && sll.head->next->next->next->data == 40);
    }

    void test_empty_list() {
        SinglyLinkedList sll;
        assert(sll.head == nullptr);
    }

    void test_search_empty_list() {
        SinglyLinkedList sll;
        bool result = sll.search(10);
        assert(result == false);
    }

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
};

int main() {
    TestSinglyLinkedList tests;
    return 0;
}
