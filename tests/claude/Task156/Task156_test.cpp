#include <iostream>
#include <sstream>
#include <string>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void preorderTraversal(TreeNode* root, std::ostream& out) {
    if (root == nullptr) return;
    out << root->val << " ";
    preorderTraversal(root->left, out);
    preorderTraversal(root->right, out);
}

void inorderTraversal(TreeNode* root, std::ostream& out) {
    if (root == nullptr) return;
    inorderTraversal(root->left, out);
    out << root->val << " ";
    inorderTraversal(root->right, out);
}

void postorderTraversal(TreeNode* root, std::ostream& out) {
    if (root == nullptr) return;
    postorderTraversal(root->left, out);
    postorderTraversal(root->right, out);
    out << root->val << " ";
}

bool runTest() {
    // Build the tree as in the Python example
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    std::stringstream output;

    output << "Preorder traversal:\n";
    preorderTraversal(root, output);

    output << "\nInorder traversal:\n";
    inorderTraversal(root, output);

    output << "\nPostorder traversal:\n";
    postorderTraversal(root, output);

    std::string expected =
        "Preorder traversal:\n"
        "1 2 4 5 3 \n"
        "Inorder traversal:\n"
        "4 2 5 1 3 \n"
        "Postorder traversal:\n"
        "4 5 2 3 1 ";

    std::string actual = output.str();

    // Clean up memory
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    if (actual == expected) {
        return true;
    } else {
        std::cerr << "Test failed.\nExpected:\n" << expected << "\nGot:\n" << actual << std::endl;
        return false;
    }
}

int main() {
    if (runTest()) {
        std::cout << "Test passed." << std::endl;
        return 0;
    } else {
        std::cout << "Test failed." << std::endl;
        return 1;
    }
}
