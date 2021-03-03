#include <iostream>
#include "any.h"

using namespace std;

int main() {
    Any any1{1};
    int a = any_cast<int>(any1);
    cout << a << endl;

    Any any2{2.0};
    double b = any_cast<double>(any2);
    cout << b << endl;

    Any any3{string{"string"}};
    string c = any_cast<string>(any3);
    cout << c << endl;
    return 0;
}