#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

Node* newNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}

void preorderTraversal(Node* root, ostream& out) {
    if (root) {
        out << root->data << " ";
        preorderTraversal(root->left, out);
        preorderTraversal(root->right, out);
    }
}

void inorderTraversal(Node* root, ostream& out) {
    if (root) {
        inorderTraversal(root->left, out);
        out << root->data << " ";
        inorderTraversal(root->right, out);
    }
}

void postorderTraversal(Node* root, ostream& out) {
    if (root) {
        postorderTraversal(root->left, out);
        postorderTraversal(root->right, out);
        out << root->data << " ";
    }
}

bool runTest() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    stringstream output;

    output << "Preorder traversal: ";
    preorderTraversal(root, output);
    output << "\n";

    output << "Inorder traversal: ";
    inorderTraversal(root, output);
    output << "\n";

    output << "Postorder traversal: ";
    postorderTraversal(root, output);
    output << "\n";

    string expected =
        "Preorder traversal: 1 2 4 5 3 \n"
        "Inorder traversal: 4 2 5 1 3 \n"
        "Postorder traversal: 4 5 2 3 1 \n";

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
