// sfinae.cpp
#include <iostream>

template<bool B, typename T>
struct enable_if {};

template<typename T>
struct enable_if<true, T> {
    using type = T;
};

int main() {
    enable_if<sizeof(int)==4, int>::type b; // ok
    // enable_if<sizeof(short)==4, short>::type a; // compile error
    return 0;
}
