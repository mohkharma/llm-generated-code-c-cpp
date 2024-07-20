#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        left = right = nullptr;
    }
};

class BinarySearchTree {
public:
    Node* root;

    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        }
        return node;
    }

    void deleteNode(int data) {
        root = deleteNode(root, data);
    }

    Node* deleteNode(Node* node, int data) {
        if (node == nullptr) {
            return node;
        }
        if (data < node->data) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->data) {
            node->right = deleteNode(node->right, data);
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
            node->data = minValue(node->right);
            node->right = deleteNode(node->right, node->data);
        }
        return node;
    }

    int minValue(Node* node) {
        int minv = node->data;
        while (node->left != nullptr) {
            minv = node->left->data;
            node = node->left;
        }
        return minv;
    }

    bool search(int data) {
        return search(root, data);
    }

    bool search(Node* node, int data) {
        if (node == nullptr) {
            return false;
        }
        if (data == node->data) {
            return true;
        }
        if (data < node->data) {
            return search(node->left, data);
        }
        return search(node->right, data);
    }

    void levelOrderTraversal() {
        if (root == nullptr) {
            return;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            cout << node->data << " ";
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
    }
};

int main() {
    BinarySearchTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    cout << "Level Order Traversal: ";
    tree.levelOrderTraversal();
    cout << endl;

    cout << "Search for 40: " << tree.search(40) << endl;
    cout << "Search for 100: " << tree.search(100) << endl;

    cout << "
Delete 20" << endl;
    tree.deleteNode(20);
    cout << "Level Order Traversal: ";
    tree.levelOrderTraversal();
    cout << endl;

    cout << "Delete 50" << endl;
    tree.deleteNode(50);
    cout << "Level Order Traversal: ";
    tree.levelOrderTraversal();
    cout << endl;

    return 0;
}