#include <iostream>

using namespace std;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;
};

// Class to represent the linked list
class LinkedList {
private:
    Node* head;

public:
    // Constructor
    LinkedList() {
        head = nullptr;
    }

    // Function to insert a new node at the beginning of the list
    void insert(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    // Function to delete a node with a given value
    void deleteNode(int value) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && current->data != value) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Value not found in the list." << endl;
            return;
        }

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;
    }

    // Function to search for a node with a given value
    bool search(int value) {
        Node* current = head;

        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    // Function to print the linked list
    void printList() {
        Node* current = head;

        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }
};

int main() {
    LinkedList list;

    list.insert(10);
    list.insert(20);
    list.insert(30);

    cout << "Linked list: ";
    list.printList();

    cout << "Searching for 20: " << list.search(20) << endl;

    list.deleteNode(20);

    cout << "Linked list after deleting 20: ";
    list.printList();

    return 0;
}