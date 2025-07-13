#include <iostream>
#include <string>

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* GetNewNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        std::cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* Insert(Node* root, int data) {
    if (root == NULL) {
        root = GetNewNode(data);
    } else if (data <= root->data) {
        root->left = Insert(root->left, data);
    } else {
        root->right = Insert(root->right, data);
    }
    return root;
}

Node* FindMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

Node* Delete(Node* root, int data) {
    Node* temp;
    if (root == NULL) return NULL;
    else if (data < root->data) root->left = Delete(root->left, data);
    else if (data > root->data) root->right = Delete(root->right, data);
    else {
        if (root->left && root->right) {
            temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, root->data);
        } else {
            temp = root;
            if (root->left == NULL) root = root->right;
            else if (root->right == NULL) root = root->left;
            delete temp;
        }
    }
    return root;
}

bool Search(Node* root, int data) {
    while (root != NULL) {
        if (root->data > data) root = root->left;
        else if (root->data < data) root = root->right;
        else return true;
    }
    return false;
}

// Test code matching the given Python tests exactly

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
        Node* root = NULL;
        root = Insert(root, 10);
        root = Insert(root, 20);
        root = Insert(root, 5);
        assertTrue(Search(root, 10), "Failed Test Case 1: test_insert_and_search");
        assertTrue(Search(root, 20), "Failed Test Case 1: test_insert_and_search");
        assertTrue(Search(root, 5), "Failed Test Case 1: test_insert_and_search");
        assertTrue(!Search(root, 15), "Failed Test Case 1: test_insert_and_search");
        freeTree(root);
    }

    void test_delete_leaf_node() {
        Node* root = NULL;
        root = Insert(root, 10);
        root = Insert(root, 5);
        root = Delete(root, 5);
        assertTrue(!Search(root, 5), "Failed Test Case 2: test_delete_leaf_node");
        freeTree(root);
    }

    void test_delete_node_with_one_child() {
        Node* root = NULL;
        root = Insert(root, 10);
        root = Insert(root, 5);
        root = Insert(root, 7);
        root = Delete(root, 5);
        assertTrue(!Search(root, 5), "Failed Test Case 3: test_delete_node_with_one_child");
        assertTrue(Search(root, 7), "Failed Test Case 3: test_delete_node_with_one_child");
        freeTree(root);
    }

    void test_delete_node_with_two_children() {
        Node* root = NULL;
        root = Insert(root, 10);
        root = Insert(root, 5);
        root = Insert(root, 15);
        root = Insert(root, 12);
        root = Delete(root, 15);
        assertTrue(!Search(root, 15), "Failed Test Case 4: test_delete_node_with_two_children");
        assertTrue(Search(root, 12), "Failed Test Case 4: test_delete_node_with_two_children");
        freeTree(root);
    }

    void test_delete_root() {
        Node* root = NULL;
        root = Insert(root, 10);
        root = Insert(root, 5);
        root = Insert(root, 15);
        root = Delete(root, 10);
        assertTrue(!Search(root, 10), "Failed Test Case 5: test_delete_root");
        assertTrue(Search(root, 5), "Failed Test Case 5: test_delete_root");
        assertTrue(Search(root, 15), "Failed Test Case 5: test_delete_root");
        freeTree(root);
    }

    void test_search_empty_tree() {
        Node* root = NULL;
        assertTrue(!Search(root, 10), "Failed Test Case 6: test_search_empty_tree");
    }

    void test_insert_multiple_nodes() {
        Node* root = NULL;
        root = Insert(root, 10);
        root = Insert(root, 5);
        root = Insert(root, 15);
        root = Insert(root, 7);
        root = Insert(root, 12);
        assertTrue(Search(root, 7), "Failed Test Case 7: test_insert_multiple_nodes");
        assertTrue(Search(root, 12), "Failed Test Case 7: test_insert_multiple_nodes");
        freeTree(root);
    }

    void test_delete_node_with_no_children() {
        Node* root = NULL;
        root = Insert(root, 10);
        root = Delete(root, 10);
        assertTrue(!Search(root, 10), "Failed Test Case 8: test_delete_node_with_no_children");
        freeTree(root);
    }

    void test_delete_node_with_left_child() {
        Node* root = NULL;
        root = Insert(root, 10);
        root = Insert(root, 5);
        root = Insert(root, 3);
        root = Delete(root, 5);
        assertTrue(!Search(root, 5), "Failed Test Case 9: test_delete_node_with_left_child");
        assertTrue(Search(root, 3), "Failed Test Case 9: test_delete_node_with_left_child");
        freeTree(root);
    }

    void test_delete_node_with_right_child() {
        Node* root = NULL;
        root = Insert(root, 10);
        root = Insert(root, 15);
        root = Insert(root, 20);
        root = Delete(root, 15);
        assertTrue(!Search(root, 15), "Failed Test Case 10: test_delete_node_with_right_child");
        assertTrue(Search(root, 20), "Failed Test Case 10: test_delete_node_with_right_child");
        freeTree(root);
    }

    void freeTree(Node* root) {
        if (!root) return;
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
};

int main() {
    TestBST tester;
    tester.run_tests();
    return 0;
}
