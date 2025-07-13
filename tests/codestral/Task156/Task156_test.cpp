#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = NULL;
    }
};

void printPreorder(Node* node, ostream& out) {
    if (node == NULL)
        return;

    out << node->data << " ";
    printPreorder(node->left, out);
    printPreorder(node->right, out);
}

void printInorder(Node* node, ostream& out) {
    if (node == NULL)
        return;

    printInorder(node->left, out);
    out << node->data << " ";
    printInorder(node->right, out);
}

void printPostorder(Node* node, ostream& out) {
    if (node == NULL)
        return;

    printPostorder(node->left, out);
    printPostorder(node->right, out);
    out << node->data << " ";
}

bool runTest() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    stringstream output;

    output << "Preorder traversal:\n";
    printPreorder(root, output);

    output << "\nInorder traversal:\n";
    printInorder(root, output);

    output << "\nPostorder traversal:\n";
    printPostorder(root, output);

    string expected =
        "Preorder traversal:\n"
        "1 2 4 5 3 \n"
        "Inorder traversal:\n"
        "4 2 5 1 3 \n"
        "Postorder traversal:\n"
        "4 5 2 3 1 ";

    // Clean up
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
