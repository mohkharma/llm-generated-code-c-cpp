#include <iostream>
#include <cassert>

struct Node {
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insert(int data) {
        if (!head) {
            head = new Node(data);
        } else {
            Node* current = head;
            while (current->next) current = current->next;
            current->next = new Node(data);
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

    void printList() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    Node* getHead() { return head; }
};

class TestLinkedList {
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
        LinkedList ll;
        ll.insert(1);
        ll.insert(2);
        assert(ll.getHead() && ll.getHead()->data == 1);
        assert(ll.getHead()->next && ll.getHead()->next->data == 2);
    }

    void test_delete() {
        LinkedList ll;
        ll.insert(1);
        ll.insert(2);
        ll.insert(3);
        ll.deleteNode(2);
        assert(ll.getHead() && ll.getHead()->data == 1);
        assert(ll.getHead()->next && ll.getHead()->next->data == 3);
    }

    void test_delete_non_existent() {
        LinkedList ll;
        ll.insert(1);
        ll.insert(2);
        ll.deleteNode(99);
        assert(ll.getHead() && ll.getHead()->data == 1);
        assert(ll.getHead()->next && ll.getHead()->next->data == 2);
    }

    void test_delete_head() {
        LinkedList ll;
        ll.insert(1);
        ll.insert(2);
        ll.deleteNode(1);
        assert(ll.getHead() && ll.getHead()->data == 2);
    }

    void test_delete_last_element() {
        LinkedList ll;
        ll.insert(1);
        ll.insert(2);
        ll.deleteNode(2);
        assert(ll.getHead() && ll.getHead()->data == 1);
        assert(ll.getHead()->next == nullptr);
    }

    void test_search_found() {
        LinkedList ll;
        ll.insert(1);
        ll.insert(2);
        assert(ll.search(2) == true);
    }

    void test_search_not_found() {
        LinkedList ll;
        ll.insert(1);
        ll.insert(2);
        assert(ll.search(99) == false);
    }

    void test_insert_multiple() {
        LinkedList ll;
        ll.insert(1);
        ll.insert(2);
        ll.insert(3);
        ll.insert(4);
        Node* h = ll.getHead();
        assert(h && h->data == 1);
        assert(h->next && h->next->data == 2);
        assert(h->next->next && h->next->next->data == 3);
        assert(h->next->next->next && h->next->next->next->data == 4);
    }

    void test_empty_list() {
        LinkedList ll;
        assert(ll.getHead() == nullptr);
    }

    void test_search_empty_list() {
        LinkedList ll;
        assert(ll.search(1) == false);
    }
};

int main() {
    TestLinkedList tests;
    tests.run_tests();
    return 0;
}
