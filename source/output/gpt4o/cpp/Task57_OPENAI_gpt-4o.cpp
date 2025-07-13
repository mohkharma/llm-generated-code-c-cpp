#include <iostream>
using namespace std;

 long long computeFactorial(int number) {
    long long factorial = 1;
    for (int i = 1; i <= number; i++) {
        factorial *= i;
    }
    return factorial;
}
