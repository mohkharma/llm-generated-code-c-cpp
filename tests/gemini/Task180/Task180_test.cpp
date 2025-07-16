#include <iostream>
#include <vector>
#include <functional>

using namespace std;

vector<int> reparentTree(const vector<int>& parentOf, int root) {
  int n = parentOf.size();
  vector<int> newParentOf(n, -1);
  vector<bool> visited(n, false);

  function<void(int)> dfs = [&](int node) {
    visited[node] = true;
    for (int child = 0; child < n; ++child) {
      if (parentOf[child] == node && !visited[child]) {
        newParentOf[child] = node;
        dfs(child);
      }
    }
    if (node != root) {
      newParentOf[node] = parentOf[node];
    }
  };

  dfs(root);
  return newParentOf;
}

void test_case(const string& test_name, const vector<int>& result, const vector<int>& expected) {
    bool pass = (result.size() == expected.size());
    for (size_t i = 0; i < result.size() && pass; ++i) {
        if (result[i] != expected[i]) {
            pass = false;
        }
    }
    if (pass) {
        cout << test_name << ": PASS\n";
    } else {
        cout << test_name << ": FAIL\nExpected: ";
        for (int v : expected) cout << v << " ";
        cout << "\nGot:      ";
        for (int v : result) cout << v << " ";
        cout << "\n";
    }
}

int main() {
    // الحالة 1 - جذر 6
    {
        vector<int> parentOf = {-1,0,0,0,1,1,2,2,3,3};
        int newRoot = 6;
        vector<int> expected = {2,0,6,0,1,1,-1,2,3,3};
        auto result = reparentTree(parentOf, newRoot);
        test_case("Test case 1 (root=6)", result, expected);
    }

    // الحالة 2 - جذر 0 (نفس الجذر الأصلي، النتيجة يجب أن تكون نفسها)
    {
        vector<int> parentOf = {-1,0,0,0,1,1,2,2,3,3};
        int newRoot = 0;
        vector<int> expected = {-1,0,0,0,1,1,2,2,3,3};
        auto result = reparentTree(parentOf, newRoot);
        test_case("Test case 2 (root=0)", result, expected);
    }

    // الحالة 3 - جذر 3
    {
        vector<int> parentOf = {-1,0,0,0,1,1,2,2,3,3};
        int newRoot = 3;
        vector<int> expected = {0,0,0,-1,1,1,2,2,3,3};
        auto result = reparentTree(parentOf, newRoot);
        test_case("Test case 3 (root=3)", result, expected);
    }

    // الحالة 4 - جذر 999 (غير موجود، يجب ترجع نفس الشجرة)
    {
        vector<int> parentOf = {-1,0,0,0,1,1,2,2,3,3};
        int newRoot = 999;
        vector<int> expected = {-1,0,0,0,1,1,2,2,3,3};
        auto result = reparentTree(parentOf, newRoot);
        test_case("Test case 4 (root=999, non-existent)", result, expected);
    }

    // الحالة 5 - شجرة صغيرة مختلفة
    {
        vector<int> parentOf = {-1,0,0,1};
        int newRoot = 1;
        vector<int> expected = {1,-1,0,1};
        auto result = reparentTree(parentOf, newRoot);
        test_case("Test case 5 (small tree, root=1)", result, expected);
    }

    return 0;
}
