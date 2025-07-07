#include <iostream>
#include <sstream>
#include <string>

class Node {
public:
    int key;
    Node *left, *right;

    Node(int item) {
        key = item;
        left = right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    Node* insertRecursive(Node* root, int key) {
        if (root == nullptr) return new Node(key);
        if (key < root->key)
            root->left = insertRecursive(root->left, key);
        else if (key > root->key)
            root->right = insertRecursive(root->right, key);
        return root;
    }

    Node* deleteRecursive(Node* root, int key) {
        if (root == nullptr) return root;
        if (key < root->key)
            root->left = deleteRecursive(root->left, key);
        else if (key > root->key)
            root->right = deleteRecursive(root->right, key);
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteRecursive(root->right, temp->key);
        }
        return root;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    bool searchRecursive(Node* root, int key) {
        if (root == nullptr || root->key == key)
            return root != nullptr;
        if (key < root->key)
            return searchRecursive(root->left, key);
        return searchRecursive(root->right, key);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int key) {
        root = insertRecursive(root, key);
    }

    void remove(int key) {
        root = deleteRecursive(root, key);
    }

    bool search(int key) {
        return searchRecursive(root, key);
    }
};

bool assertTrue(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << message << std::endl;
        return false;
    }
    return true;
}

class TestBinarySearchTree {
public:
    void run_tests() {
        test_insert_and_search();
        test_delete_leaf_node();
        test_delete_node_with_one_child();
        test_delete_node_with_two_children();
        test_delete_root();
        test_search_empty_tree();
        test_insert_multiple_nodes();
        test_delete_node_with_no_children();
        test_delete_node_with_left_child();
        test_delete_node_with_right_child();
        std::cout << "All test cases passed!" << std::endl;
    }

private:
    void test_insert_and_search() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(20);
        bst.insert(5);
        assertTrue(bst.search(10), "Failed Test Case 1: test_insert_and_search");
        assertTrue(bst.search(20), "Failed Test Case 1: test_insert_and_search");
        assertTrue(bst.search(5), "Failed Test Case 1: test_insert_and_search");
        assertTrue(!bst.search(15), "Failed Test Case 1: test_insert_and_search");
    }

    void test_delete_leaf_node() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(5);
        bst.remove(5);
        assertTrue(!bst.search(5), "Failed Test Case 2: test_delete_leaf_node");
    }

    void test_delete_node_with_one_child() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(7);
        bst.remove(5);
        assertTrue(!bst.search(5), "Failed Test Case 3: test_delete_node_with_one_child");
        assertTrue(bst.search(7), "Failed Test Case 3: test_delete_node_with_one_child");
    }

    void test_delete_node_with_two_children() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.insert(12);
        bst.remove(15);
        assertTrue(!bst.search(15), "Failed Test Case 4: test_delete_node_with_two_children");
        assertTrue(bst.search(12), "Failed Test Case 4: test_delete_node_with_two_children");
    }

    void test_delete_root() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.remove(10);
        assertTrue(!bst.search(10), "Failed Test Case 5: test_delete_root");
        assertTrue(bst.search(5), "Failed Test Case 5: test_delete_root");
        assertTrue(bst.search(15), "Failed Test Case 5: test_delete_root");
    }

    void test_search_empty_tree() {
        BinarySearchTree bst;
        assertTrue(!bst.search(10), "Failed Test Case 6: test_search_empty_tree");
    }

    void test_insert_multiple_nodes() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.insert(7);
        bst.insert(12);
        assertTrue(bst.search(7), "Failed Test Case 7: test_insert_multiple_nodes");
        assertTrue(bst.search(12), "Failed Test Case 7: test_insert_multiple_nodes");
    }

    void test_delete_node_with_no_children() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.remove(10);
        assertTrue(!bst.search(10), "Failed Test Case 8: test_delete_node_with_no_children");
    }

    void test_delete_node_with_left_child() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(3);
        bst.remove(5);
        assertTrue(!bst.search(5), "Failed Test Case 9: test_delete_node_with_left_child");
        assertTrue(bst.search(3), "Failed Test Case 9: test_delete_node_with_left_child");
    }

    void test_delete_node_with_right_child() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(15);
        bst.insert(20);
        bst.remove(15);
        assertTrue(!bst.search(15), "Failed Test Case 10: test_delete_node_with_right_child");
        assertTrue(bst.search(20), "Failed Test Case 10: test_delete_node_with_right_child");
    }
};

int main() {
    TestBinarySearchTree tests;
    tests.run_tests();
    return 0;
}
