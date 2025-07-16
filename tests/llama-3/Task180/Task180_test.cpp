#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node {
public:
    int value;
    vector<Node*> children;

    Node(int value) : value(value) {}
};

Node* reparentTree(Node* root, Node* newRoot) {
    if (root == newRoot) {
        return root;
    }
    queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node* node = queue.front();
        queue.pop();
        if (node == newRoot) {
            return node;
        }
        for (Node* child : node->children) {
            queue.push(child);
        }
    }
    return nullptr;
}

void printTree(Node* node, int level) {
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
    cout << node->value << endl;
    for (Node* child : node->children) {
        printTree(child, level + 1);
    }
}

// دالة مساعدة لطباعة نتيجة الاختبار
void test_case(const string& test_name, bool condition) {
    if (condition)
        cout << test_name << ": PASS" << endl;
    else
        cout << test_name << ": FAIL" << endl;
}

// إنشاء الشجرة الأساسية واسترجاع عقد معينة لتسهيل الاختبار
struct TreeAndNodes {
    Node* root;
    Node* n0;
    Node* n1;
    Node* n2;
    Node* n3;
    Node* n4;
    Node* n5;
    Node* n6;
    Node* n7;
    Node* n8;
    Node* n9;
};

TreeAndNodes buildTree() {
    Node* n0 = new Node(0);
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
    Node* n8 = new Node(8);
    Node* n9 = new Node(9);

    n0->children.push_back(n1);
    n0->children.push_back(n2);
    n0->children.push_back(n3);
    n1->children.push_back(n4);
    n1->children.push_back(n5);
    n2->children.push_back(n6);
    n2->children.push_back(n7);
    n3->children.push_back(n8);
    n3->children.push_back(n9);

    return {n0, n0, n1, n2, n3, n4, n5, n6, n7, n8, n9};
}

int main() {
    TreeAndNodes t = buildTree();

    // Test 1: إعادة التوجيه إلى العقدة 6 (موجودة)
    {
        Node* result = reparentTree(t.root, t.n6);
        test_case("Test 1 - reparent to node 6", result != nullptr && result->value == 6);
    }

    // Test 2: إعادة التوجيه إلى العقدة 0 (الجذر نفسه)
    {
        Node* result = reparentTree(t.root, t.n0);
        test_case("Test 2 - reparent to node 0 (root)", result != nullptr && result->value == 0);
    }

    // Test 3: إعادة التوجيه إلى العقدة 9 (موجودة)
    {
        Node* result = reparentTree(t.root, t.n9);
        test_case("Test 3 - reparent to node 9", result != nullptr && result->value == 9);
    }

    // Test 4: إعادة التوجيه إلى عقدة غير موجودة (nullptr)
    {
        Node* fakeNode = new Node(999);  // غير موجود في الشجرة
        Node* result = reparentTree(t.root, fakeNode);
        test_case("Test 4 - reparent to non-existent node", result == nullptr);
        delete fakeNode;
    }

    // Test 5: إعادة التوجيه إلى عقدة داخل الشجرة (مثلاً 3)
    {
        Node* result = reparentTree(t.root, t.n3);
        test_case("Test 5 - reparent to node 3", result != nullptr && result->value == 3);
    }

    return 0;
}
