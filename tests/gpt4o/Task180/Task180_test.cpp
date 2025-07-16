#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
public:
    int val;
    vector<TreeNode*> children;

    TreeNode(int val) {
        this->val = val;
    }
};

TreeNode* reorientTree(TreeNode* node) {
    TreeNode* root = new TreeNode(node->val);
    for (TreeNode* child : node->children) {
        TreeNode* childNode = reorientTree(child);
        root->children.push_back(childNode);
    }
    return root;
}

int countNodes(TreeNode* node) {
    if (!node) return 0;
    int cnt = 1;
    for (auto c : node->children)
        cnt += countNodes(c);
    return cnt;
}

int countChildren(TreeNode* node) {
    if (!node) return 0;
    int count = (int)node->children.size();
    for (auto c : node->children) {
        count += countChildren(c);
    }
    return count;
}

void test_case(const string& test_name, bool condition) {
    if (condition)
        cout << test_name << ": PASS" << endl;
    else
        cout << test_name << ": FAIL" << endl;
}

TreeNode* buildOriginalTree() {
    TreeNode* n0 = new TreeNode(0);
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n6 = new TreeNode(6);
    TreeNode* n7 = new TreeNode(7);
    TreeNode* n8 = new TreeNode(8);
    TreeNode* n9 = new TreeNode(9);

    n0->children.push_back(n1);
    n0->children.push_back(n2);
    n0->children.push_back(n3);
    n1->children.push_back(n4);
    n1->children.push_back(n5);
    n2->children.push_back(n6);
    n2->children.push_back(n7);
    n3->children.push_back(n8);
    n3->children.push_back(n9);

    return n0;
}

int main() {
    // Test case 1: reorient with root=6 (leaf node)
    {
        TreeNode* root = buildOriginalTree();
        TreeNode* newRoot = reorientTree(root->children[1]->children[0]); // node 6
        test_case("Test 1 - root val == 6", newRoot->val == 6);
        test_case("Test 1 - root has no children", newRoot->children.size() == 0);
        test_case("Test 1 - total nodes count == 1", countNodes(newRoot) == 1);
    }

    // Test case 2: reorient with root=2 (internal node)
    {
        TreeNode* root = buildOriginalTree();
        TreeNode* newRoot = reorientTree(root->children[1]); // node 2
        test_case("Test 2 - root val == 2", newRoot->val == 2);
        test_case("Test 2 - root children count == 2", newRoot->children.size() == 2);
        test_case("Test 2 - total nodes count == 3", countNodes(newRoot) == 3);
    }

    // Test case 3: reorient with root=0 (original root)
    {
        TreeNode* root = buildOriginalTree();
        TreeNode* newRoot = reorientTree(root); // node 0
        test_case("Test 3 - root val == 0", newRoot->val == 0);
        test_case("Test 3 - root children count == 3", newRoot->children.size() == 3);
        test_case("Test 3 - total nodes count == 10", countNodes(newRoot) == 10);
    }

    // Test case 4: reorient with root=3 (leaf parent)
    {
        TreeNode* root = buildOriginalTree();
        TreeNode* newRoot = reorientTree(root->children[2]); // node 3
        test_case("Test 4 - root val == 3", newRoot->val == 3);
        test_case("Test 4 - root children count == 2", newRoot->children.size() == 2);
        test_case("Test 4 - total nodes count == 3", countNodes(newRoot) == 3);
    }

    // Test case 5: reorient with root=1 (internal node)
    {
        TreeNode* root = buildOriginalTree();
        TreeNode* newRoot = reorientTree(root->children[0]); // node 1
        test_case("Test 5 - root val == 1", newRoot->val == 1);
        test_case("Test 5 - root children count == 2", newRoot->children.size() == 2);
        test_case("Test 5 - total nodes count == 3", countNodes(newRoot) == 3);
    }

    return 0;
}
