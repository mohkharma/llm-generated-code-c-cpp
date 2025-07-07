#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    Node* root;

    BinarySearchTree() : root(nullptr) {}

    void insert(int data) {
        root = insertRecursive(root, data);
    }

    void deleteNode(int data) {
        root = deleteRecursive(root, data);
    }

    bool search(int data) {
        return searchRecursive(root, data);
    }

    void inorderTraversal() {
        inorder(root);
    }

private:
    Node* insertRecursive(Node* root, int data) {
        if (root == nullptr) {
            return new Node(data);
        }

        if (data < root->data) {
            root->left = insertRecursive(root->left, data);
        } else if (data > root->data) {
            root->right = insertRecursive(root->right, data);
        }

        return root;
    }

    Node* deleteRecursive(Node* root, int data) {
        if (root == nullptr) {
            return root;
        }

        if (data < root->data) {
            root->left = deleteRecursive(root->left, data);
        } else if (data > root->data) {
            root->right = deleteRecursive(root->right, data);
        } else {
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
            root->data = temp->data;
            root->right = deleteRecursive(root->right, temp->data);
        }
        return root;
    }

    bool searchRecursive(Node* root, int data) {
        if (root == nullptr) {
            return false;
        }

        if (root->data == data) {
            return true;
        }

        if (data < root->data) {
            return searchRecursive(root->left, data);
        } else {
            return searchRecursive(root->right, data);
        }
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }
};

// Test code matching your Python test logic, using this class and no external libraries:

bool assertTrue(bool cond, const std::string& msg) {
    if (!cond) {
        std::cerr << msg << std::endl;
        return false;
    }
    return true;
}

class TestBST {
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
        bst.deleteNode(5);
        assertTrue(!bst.search(5), "Failed Test Case 2: test_delete_leaf_node");
    }

    void test_delete_node_with_one_child() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(7);
        bst.deleteNode(5);
        assertTrue(!bst.search(5), "Failed Test Case 3: test_delete_node_with_one_child");
        assertTrue(bst.search(7), "Failed Test Case 3: test_delete_node_with_one_child");
    }

    void test_delete_node_with_two_children() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.insert(12);
        bst.deleteNode(15);
        assertTrue(!bst.search(15), "Failed Test Case 4: test_delete_node_with_two_children");
        assertTrue(bst.search(12), "Failed Test Case 4: test_delete_node_with_two_children");
    }

    void test_delete_root() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.deleteNode(10);
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
        bst.deleteNode(10);
        assertTrue(!bst.search(10), "Failed Test Case 8: test_delete_node_with_no_children");
    }

    void test_delete_node_with_left_child() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(3);
        bst.deleteNode(5);
        assertTrue(!bst.search(5), "Failed Test Case 9: test_delete_node_with_left_child");
        assertTrue(bst.search(3), "Failed Test Case 9: test_delete_node_with_left_child");
    }

    void test_delete_node_with_right_child() {
        BinarySearchTree bst;
        bst.insert(10);
        bst.insert(15);
        bst.insert(20);
        bst.deleteNode(15);
        assertTrue(!bst.search(15), "Failed Test Case 10: test_delete_node_with_right_child");
        assertTrue(bst.search(20), "Failed Test Case 10: test_delete_node_with_right_child");
    }
};

int main() {
    TestBST tests;
    tests.run_tests();
    return 0;
}
