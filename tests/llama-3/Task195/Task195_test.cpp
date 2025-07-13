#include <iostream>
#include <cmath>

#include "../../../source/output/llama-3/cpp/Task195_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

using namespace std;

bool assertAlmostEqual(double a, double b, double tol = 1e-5) {
    return fabs(a - b) <= tol;
}

int main() {
    int passed = 0, total = 0;

    {
        total++;
        MedianFinder mf;
        mf.addNum(1);
        if (assertAlmostEqual(mf.findMedian(), 1.0)) passed++;
        else cout << "❌ Failed test 1\n";
    }

    {
        total++;
        MedianFinder mf;
        mf.addNum(1);
        mf.addNum(2);
        if (assertAlmostEqual(mf.findMedian(), 1.5)) passed++;
        else cout << "❌ Failed test 2\n";
    }

    {
        total++;
        MedianFinder mf;
        mf.addNum(1);
        mf.addNum(2);
        mf.addNum(3);
        if (assertAlmostEqual(mf.findMedian(), 2.0)) passed++;
        else cout << "❌ Failed test 3\n";
    }

    {
        total++;
        MedianFinder mf;
        mf.addNum(3);
        mf.addNum(1);
        mf.addNum(4);
        mf.addNum(2);
        mf.addNum(5);
        if (assertAlmostEqual(mf.findMedian(), 3.0)) passed++;
        else cout << "❌ Failed test 4\n";
    }

    {
        total++;
        MedianFinder mf;
        mf.addNum(10);
        mf.addNum(5);
        mf.addNum(15);
        mf.addNum(20);
        mf.addNum(25);
        mf.addNum(30);
        if (assertAlmostEqual(mf.findMedian(), 17.5)) passed++;
        else cout << "❌ Failed test 5\n";
    }

    {
        total++;
        MedianFinder mf;
        mf.addNum(0);
        mf.addNum(0);
        mf.addNum(0);
        if (assertAlmostEqual(mf.findMedian(), 0.0)) passed++;
        else cout << "❌ Failed test 6\n";
    }

    {
        total++;
        MedianFinder mf;
        mf.addNum(-1);
        mf.addNum(0);
        mf.addNum(1);
        if (assertAlmostEqual(mf.findMedian(), 0.0)) passed++;
        else cout << "❌ Failed test 7\n";
    }

    {
        total++;
        MedianFinder mf;
        mf.addNum(-10);
        mf.addNum(-20);
        mf.addNum(-30);
        mf.addNum(-40);
        mf.addNum(-50);
        if (assertAlmostEqual(mf.findMedian(), -30.0)) passed++;
        else cout << "❌ Failed test 8\n";
    }

    {
        total++;
        MedianFinder mf;
        mf.addNum(100);
        mf.addNum(200);
        mf.addNum(300);
        mf.addNum(400);
        mf.addNum(500);
        mf.addNum(600);
        mf.addNum(700);
        if (assertAlmostEqual(mf.findMedian(), 400.0)) passed++;
        else cout << "❌ Failed test 9\n";
    }

    {
        total++;
        MedianFinder mf;
        mf.addNum(1);
        mf.addNum(3);
        mf.addNum(2);
        mf.addNum(4);
        mf.addNum(5);
        mf.addNum(6);
        mf.addNum(7);
        mf.addNum(8);
        mf.addNum(9);
        if (assertAlmostEqual(mf.findMedian(), 5.0)) passed++;
        else cout << "❌ Failed test 10\n";
    }

    cout << "\n✅ Summary: " << passed << " / " << total << " tests passed.\n";
    return 0;
}
