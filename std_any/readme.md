A naive implementation of std::any in c++17.

- [1. implementation](#1-implementation)
- [2. useage](#2-useage)

# 1. implementation
- use a void* pointer to store the raw data.
- get its runtime type by calling typeid.
- store the runtime info into std::functions so that the *Any* class is copyable just like the std::any.

# 2. useage
```cpp
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
```