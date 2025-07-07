#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Node {
public:
    int key;
    Node* left, * right;

    Node(int item) {
        key = item;
        left = right = nullptr;
    }
};

void inorder(Node* node, ostream& out) {
    if (node == nullptr)
        return;

    inorder(node->left, out);
    out << node->key << " ";
    inorder(node->right, out);
}

bool runTest() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    stringstream output;
    output << "Inorder traversal of binary tree is ";
    inorder(root, output);

    string expected = "Inorder traversal of binary tree is 4 2 5 1 3 ";

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
