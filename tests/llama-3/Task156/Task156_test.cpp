#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

void preorder_traversal(Node* node, ostream& out) {
    if (node == nullptr)
        return;
    out << node->data << " ";
    preorder_traversal(node->left, out);
    preorder_traversal(node->right, out);
}

void inorder_traversal(Node* node, ostream& out) {
    if (node == nullptr)
        return;
    inorder_traversal(node->left, out);
    out << node->data << " ";
    inorder_traversal(node->right, out);
}

void postorder_traversal(Node* node, ostream& out) {
    if (node == nullptr)
        return;
    postorder_traversal(node->left, out);
    postorder_traversal(node->right, out);
    out << node->data << " ";
}

bool runTest() {
    Node* root = new Node{1};
    root->left = new Node{2};
    root->right = new Node{3};
    root->left->left = new Node{4};
    root->left->right = new Node{5};

    stringstream output;
    output << "Preorder traversal: ";
    preorder_traversal(root, output);

    output << "\nInorder traversal: ";
    inorder_traversal(root, output);

    output << "\nPostorder traversal: ";
    postorder_traversal(root, output);

    string expected =
        "Preorder traversal: 1 2 4 5 3 \n"
        "Inorder traversal: 4 2 5 1 3 \n"
        "Postorder traversal: 4 5 2 3 1 ";

    // Clean up memory
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    if (output.str() == expected) {
        return true;
    } else {
        cerr << "Test failed.\nExpected:\n" << expected << "\nGot:\n" << output.str() << endl;
        return false;
    }
}

int main() {
    if (runTest()) {
        cout << "Test passed." << endl;
        return 0;
    } else {
        cout << "Test failed." << endl;
        return 1;
    }
}
