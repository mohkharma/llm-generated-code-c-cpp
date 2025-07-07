#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left, * right;
};

Node* newNode(int item) {
    Node* temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

Node* insert(Node* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (root->key < key)
        return search(root->right, key);
    return search(root->left, key);
}

// Helper to free allocated memory in the tree
void freeTree(Node* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Test suite matching the Python test logic strictly
bool assertTrue(bool cond, const string& msg) {
    if (!cond) {
        cerr << msg << endl;
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
        cout << "All test cases passed!" << endl;
    }
private:
    void test_insert_and_search() {
        Node* root = nullptr;
        root = insert(root, 10);
        root = insert(root, 20);
        root = insert(root, 5);
        assertTrue(search(root, 10) != nullptr, "Failed Test Case 1: test_insert_and_search");
        assertTrue(search(root, 20) != nullptr, "Failed Test Case 1: test_insert_and_search");
        assertTrue(search(root, 5) != nullptr, "Failed Test Case 1: test_insert_and_search");
        assertTrue(search(root, 15) == nullptr, "Failed Test Case 1: test_insert_and_search");
        freeTree(root);
    }

    void test_delete_leaf_node() {
        Node* root = nullptr;
        root = insert(root, 10);
        root = insert(root, 5);
        root = deleteNode(root, 5);
        assertTrue(search(root, 5) == nullptr, "Failed Test Case 2: test_delete_leaf_node");
        freeTree(root);
    }

    void test_delete_node_with_one_child() {
        Node* root = nullptr;
        root = insert(root, 10);
        root = insert(root, 5);
        root = insert(root, 7);
        root = deleteNode(root, 5);
        assertTrue(search(root, 5) == nullptr, "Failed Test Case 3: test_delete_node_with_one_child");
        assertTrue(search(root, 7) != nullptr, "Failed Test Case 3: test_delete_node_with_one_child");
        freeTree(root);
    }

    void test_delete_node_with_two_children() {
        Node* root = nullptr;
        root = insert(root, 10);
        root = insert(root, 5);
        root = insert(root, 15);
        root = insert(root, 12);
        root = deleteNode(root, 15);
        assertTrue(search(root, 15) == nullptr, "Failed Test Case 4: test_delete_node_with_two_children");
        assertTrue(search(root, 12) != nullptr, "Failed Test Case 4: test_delete_node_with_two_children");
        freeTree(root);
    }

    void test_delete_root() {
        Node* root = nullptr;
        root = insert(root, 10);
        root = insert(root, 5);
        root = insert(root, 15);
        root = deleteNode(root, 10);
        assertTrue(search(root, 10) == nullptr, "Failed Test Case 5: test_delete_root");
        assertTrue(search(root, 5) != nullptr, "Failed Test Case 5: test_delete_root");
        assertTrue(search(root, 15) != nullptr, "Failed Test Case 5: test_delete_root");
        freeTree(root);
    }

    void test_search_empty_tree() {
        Node* root = nullptr;
        assertTrue(search(root, 10) == nullptr, "Failed Test Case 6: test_search_empty_tree");
    }

    void test_insert_multiple_nodes() {
        Node* root = nullptr;
        root = insert(root, 10);
        root = insert(root, 5);
        root = insert(root, 15);
        root = insert(root, 7);
        root = insert(root, 12);
        assertTrue(search(root, 7) != nullptr, "Failed Test Case 7: test_insert_multiple_nodes");
        assertTrue(search(root, 12) != nullptr, "Failed Test Case 7: test_insert_multiple_nodes");
        freeTree(root);
    }

    void test_delete_node_with_no_children() {
        Node* root = nullptr;
        root = insert(root, 10);
        root = deleteNode(root, 10);
        assertTrue(search(root, 10) == nullptr, "Failed Test Case 8: test_delete_node_with_no_children");
        freeTree(root);
    }

    void test_delete_node_with_left_child() {
        Node* root = nullptr;
        root = insert(root, 10);
        root = insert(root, 5);
        root = insert(root, 3);
        root = deleteNode(root, 5);
        assertTrue(search(root, 5) == nullptr, "Failed Test Case 9: test_delete_node_with_left_child");
        assertTrue(search(root, 3) != nullptr, "Failed Test Case 9: test_delete_node_with_left_child");
        freeTree(root);
    }

    void test_delete_node_with_right_child() {
        Node* root = nullptr;
        root = insert(root, 10);
        root = insert(root, 15);
        root = insert(root, 20);
        root = deleteNode(root, 15);
        assertTrue(search(root, 15) == nullptr, "Failed Test Case 10: test_delete_node_with_right_child");
        assertTrue(search(root, 20) != nullptr, "Failed Test Case 10: test_delete_node_with_right_child");
        freeTree(root);
    }
};

int main() {
    TestBST tester;
    tester.run_tests();
    return 0;
}
