#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

class Node {
public:
    int data;
    std::vector<Node*> children;

    Node(int data) : data(data) {}
};

Node* findNode(Node* node, int data) {
    if (node->data == data) {
        return node;
    }
    for (Node* child : node->children) {
        Node* result = findNode(child, data);
        if (result) {
            return result;
        }
    }
    return nullptr;
}

void reparentHelper(Node* node, Node* parent) {
    if (parent) {
        node->children.erase(std::remove(node->children.begin(), node->children.end(), parent), node->children.end());
        node->children.push_back(parent);
    }
    for (Node* child : std::vector<Node*>(node->children)) {
        if (child != parent) {
            reparentHelper(child, node);
        }
    }
}

Node* reparent(Node* root, int newRootData) {
    Node* newRoot = findNode(root, newRootData);
    if (!newRoot) {
        return root;
    }

    reparentHelper(newRoot, nullptr);
    return newRoot;
}

void printTree(Node* node, int level = 0) {
    std::cout << std::string(level * 2, ' ') << node->data << std::endl;
    for (Node* child : node->children) {
        printTree(child, level + 1);
    }
}

// دالة مساعدة لطباعة النتيجة
void test_case(const std::string& test_name, bool condition) {
    if (condition) {
        std::cout << test_name << ": PASS" << std::endl;
    } else {
        std::cout << test_name << ": FAIL" << std::endl;
    }
}

// دوال التست

// بناء شجرة افتراضية لاختبار التوجيه
Node* build_test_tree() {
    Node* root = new Node(0);
    root->children = {new Node(1), new Node(2), new Node(3)};
    root->children[0]->children = {new Node(4), new Node(5)};
    root->children[1]->children = {new Node(6), new Node(7)};
    root->children[2]->children = {new Node(8), new Node(9)};
    return root;
}

void test_reparent_existing_node() {
    Node* root = build_test_tree();
    Node* newRoot = reparent(root, 6);

    test_case("test_reparent_existing_node - new root data", newRoot->data == 6);

    // من المفترض أن 2 هو parent ل6 حاليا وليس من أطفاله
    bool isParentRemoved = std::find(newRoot->children.begin(), newRoot->children.end(), findNode(newRoot, 2)) == newRoot->children.end();
    test_case("test_reparent_existing_node - parent removed from children", isParentRemoved);

    // اختبار أن 7 هو طفل 6 (كما في الهيكل الأصلي)
    bool childExists = std::find(newRoot->children.begin(), newRoot->children.end(), findNode(newRoot, 7)) != newRoot->children.end();
    test_case("test_reparent_existing_node - child present", childExists);
}

void test_reparent_non_existing_node() {
    Node* root = build_test_tree();
    Node* newRoot = reparent(root, 999); // عقدة غير موجودة

    // يجب أن يرجع الجذر الأصلي بدون تغيير
    test_case("test_reparent_non_existing_node - root unchanged", newRoot == root);
}

void test_reparent_original_root() {
    Node* root = build_test_tree();
    Node* newRoot = reparent(root, 0); // إعادة التوجيه إلى نفس الجذر

    test_case("test_reparent_original_root - root unchanged", newRoot == root);
}

int main() {
    test_reparent_existing_node();
    test_reparent_non_existing_node();
    test_reparent_original_root();

    return 0;
}
