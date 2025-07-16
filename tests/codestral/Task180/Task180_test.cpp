#include <iostream>
#include <vector>
#include <algorithm>

class Node {
public:
    int data;
    std::vector<Node*> children;

    Node(int data) {
        this->data = data;
    }

    void reparent(Node* parent) {
        children.erase(std::remove_if(children.begin(), children.end(),
                                      [parent](Node* child) { return child == parent; }),
                       children.end());
        for (Node* child : children) {
            child->reparent(this);
        }
    }

    void printTree(int level) {
        for (int i = 0; i < level; i++) {
            std::cout << " ";
        }
        std::cout << data << std::endl;
        for (Node* child : children) {
            child->printTree(level + 1);
        }
    }
};

// دالة مساعدة لطباعة نتيجة التست
void test_case(const std::string& name, bool condition) {
    if (condition)
        std::cout << name << ": PASS\n";
    else
        std::cout << name << ": FAIL\n";
}

// دالة مساعدة للبحث عن Node في الشجرة
Node* findNode(Node* root, int data) {
    if (root->data == data)
        return root;
    for (Node* child : root->children) {
        Node* found = findNode(child, data);
        if (found)
            return found;
    }
    return nullptr;
}

// بناء شجرة اختبار
Node* build_test_tree() {
    Node* root = new Node(0);
    root->children = {new Node(1), new Node(2), new Node(3)};
    root->children[0]->children = {new Node(4), new Node(5)};
    root->children[1]->children = {new Node(6), new Node(7)};
    root->children[2]->children = {new Node(8), new Node(9)};
    return root;
}

// اختبار إعادة التوجيه لعقدة موجودة
void test_reparent_existing_node() {
    Node* root = build_test_tree();
    Node* newRoot = findNode(root, 6);
    if (newRoot)
        newRoot->reparent(nullptr);

    test_case("test_reparent_existing_node - new root data", newRoot && newRoot->data == 6);

    // الوالد 2 يجب أن لا يكون من أطفال 6
    Node* parent = findNode(root, 2);
    bool parentIsChild = false;
    if (newRoot) {
        parentIsChild = std::find(newRoot->children.begin(), newRoot->children.end(), parent) != newRoot->children.end();
    }
    test_case("test_reparent_existing_node - parent removed from children", !parentIsChild);

    // طفل 7 يجب أن يبقى من أطفال 6
    Node* child7 = findNode(root, 7);
    bool child7IsChild = false;
    if (newRoot) {
        child7IsChild = std::find(newRoot->children.begin(), newRoot->children.end(), child7) != newRoot->children.end();
    }
    test_case("test_reparent_existing_node - child present", child7IsChild);
}

// اختبار إعادة التوجيه لعقدة غير موجودة (يجب لا يتغير شيء)
void test_reparent_non_existing_node() {
    Node* root = build_test_tree();
    Node* nonExist = findNode(root, 999);
    bool unchanged = (nonExist == nullptr);
    test_case("test_reparent_non_existing_node - node does not exist", unchanged);
}

// اختبار إعادة التوجيه للجذر نفسه (لا تغيير)
void test_reparent_original_root() {
    Node* root = build_test_tree();
    root->reparent(nullptr); // إعادة التوجيه للجذر نفسه (nullptr كوالد)
    test_case("test_reparent_original_root - root unchanged data", root->data == 0);
}

int main() {
    test_reparent_existing_node();
    test_reparent_non_existing_node();
    test_reparent_original_root();
    return 0;
}
