// loop-unrolling.cpp
#include <iostream>

template<int N>
class sum {
    public: const static int ret = sum<N-1>::ret + N;
};

template<>
class sum<0> {
    public: const static int ret = 0;
};

int main() {
    std::cout << sum<5>::ret << std::endl;
    return 0;
}
