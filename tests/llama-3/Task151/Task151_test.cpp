#include <iostream>
#include <string>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int item) {
        val = item;
        left = right = nullptr;
    }
};

class BinaryTree {
public:
    Node* root = nullptr;

    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->val) {
            node->left = insert(node->left, val);
        } else if (val > node->val) {
            node->right = insert(node->right, val);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* node, int val) {
        if (node == nullptr) {
            return node;
        }
        if (val < node->val) {
            node->left = deleteNode(node->left, val);
        } else if (val > node->val) {
            node->right = deleteNode(node->right, val);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->val = temp->val;
            node->right = deleteNode(node->right, temp->val);
        }
        return node;
    }

    Node* searchNode(Node* node, int val) {
        if (node == nullptr || node->val == val) {
            return node;
        }
        if (val < node->val) {
            return searchNode(node->left, val);
        } else {
            return searchNode(node->right, val);
        }
    }
};

// دالة assert مثل بايثون
bool assertTrue(bool condition, const string& message) {
    if (!condition) {
        cerr << message << endl;
        return false;
    }
    return true;
}

class TestBinaryTree {
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
        BinaryTree tree;
        tree.root = tree.insert(tree.root, 10);
        tree.root = tree.insert(tree.root, 20);
        tree.root = tree.insert(tree.root, 5);
        assertTrue(tree.searchNode(tree.root, 10) != nullptr, "Failed Test Case 1: test_insert_and_search");
        assertTrue(tree.searchNode(tree.root, 20) != nullptr, "Failed Test Case 1: test_insert_and_search");
        assertTrue(tree.searchNode(tree.root, 5) != nullptr, "Failed Test Case 1: test_insert_and_search");
        assertTrue(tree.searchNode(tree.root, 15) == nullptr, "Failed Test Case 1: test_insert_and_search");
    }

    void test_delete_leaf_node() {
        BinaryTree tree;
        tree.root = tree.insert(tree.root, 10);
        tree.root = tree.insert(tree.root, 5);
        tree.root = tree.deleteNode(tree.root, 5);
        assertTrue(tree.searchNode(tree.root, 5) == nullptr, "Failed Test Case 2: test_delete_leaf_node");
    }

    void test_delete_node_with_one_child() {
        BinaryTree tree;
        tree.root = tree.insert(tree.root, 10);
        tree.root = tree.insert(tree.root, 5);
        tree.root = tree.insert(tree.root, 7);
        tree.root = tree.deleteNode(tree.root, 5);
        assertTrue(tree.searchNode(tree.root, 5) == nullptr, "Failed Test Case 3: test_delete_node_with_one_child");
        assertTrue(tree.searchNode(tree.root, 7) != nullptr, "Failed Test Case 3: test_delete_node_with_one_child");
    }

    void test_delete_node_with_two_children() {
        BinaryTree tree;
        tree.root = tree.insert(tree.root, 10);
        tree.root = tree.insert(tree.root, 5);
        tree.root = tree.insert(tree.root, 15);
        tree.root = tree.insert(tree.root, 12);
        tree.root = tree.deleteNode(tree.root, 15);
        assertTrue(tree.searchNode(tree.root, 15) == nullptr, "Failed Test Case 4: test_delete_node_with_two_children");
        assertTrue(tree.searchNode(tree.root, 12) != nullptr, "Failed Test Case 4: test_delete_node_with_two_children");
    }

    void test_delete_root() {
        BinaryTree tree;
        tree.root = tree.insert(tree.root, 10);
        tree.root = tree.insert(tree.root, 5);
        tree.root = tree.insert(tree.root, 15);
        tree.root = tree.deleteNode(tree.root, 10);
        assertTrue(tree.searchNode(tree.root, 10) == nullptr, "Failed Test Case 5: test_delete_root");
        assertTrue(tree.searchNode(tree.root, 5) != nullptr, "Failed Test Case 5: test_delete_root");
        assertTrue(tree.searchNode(tree.root, 15) != nullptr, "Failed Test Case 5: test_delete_root");
    }

    void test_search_empty_tree() {
        BinaryTree tree;
        assertTrue(tree.searchNode(tree.root, 10) == nullptr, "Failed Test Case 6: test_search_empty_tree");
    }

    void test_insert_multiple_nodes() {
        BinaryTree tree;
        tree.root = tree.insert(tree.root, 10);
        tree.root = tree.insert(tree.root, 5);
        tree.root = tree.insert(tree.root, 15);
        tree.root = tree.insert(tree.root, 7);
        tree.root = tree.insert(tree.root, 12);
        assertTrue(tree.searchNode(tree.root, 7) != nullptr, "Failed Test Case 7: test_insert_multiple_nodes");
        assertTrue(tree.searchNode(tree.root, 12) != nullptr, "Failed Test Case 7: test_insert_multiple_nodes");
    }

    void test_delete_node_with_no_children() {
        BinaryTree tree;
        tree.root = tree.insert(tree.root, 10);
        tree.root = tree.deleteNode(tree.root, 10);
        assertTrue(tree.searchNode(tree.root, 10) == nullptr, "Failed Test Case 8: test_delete_node_with_no_children");
    }

    void test_delete_node_with_left_child() {
        BinaryTree tree;
        tree.root = tree.insert(tree.root, 10);
        tree.root = tree.insert(tree.root, 5);
        tree.root = tree.insert(tree.root, 3);
        tree.root = tree.deleteNode(tree.root, 5);
        assertTrue(tree.searchNode(tree.root, 5) == nullptr, "Failed Test Case 9: test_delete_node_with_left_child");
        assertTrue(tree.searchNode(tree.root, 3) != nullptr, "Failed Test Case 9: test_delete_node_with_left_child");
    }

    void test_delete_node_with_right_child() {
        BinaryTree tree;
        tree.root = tree.insert(tree.root, 10);
        tree.root = tree.insert(tree.root, 15);
        tree.root = tree.insert(tree.root, 20);
        tree.root = tree.deleteNode(tree.root, 15);
        assertTrue(tree.searchNode(tree.root, 15) == nullptr, "Failed Test Case 10: test_delete_node_with_right_child");
        assertTrue(tree.searchNode(tree.root, 20) != nullptr, "Failed Test Case 10: test_delete_node_with_right_child");
    }
};

int main() {
    TestBinaryTree test;
    test.run_tests();
    return 0;
}
