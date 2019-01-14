// traits.cpp
#include <iostream>
#include <vector>

template<typename T>
class traits {
public: typedef typename T::value_type type;
};

template<typename T>
class traits<T*> {
public: typedef T type;
};

template<typename iter>
typename traits<iter>::type sum(iter _begin, iter _end) {
    typename traits<iter>::type ret{0};
    for (auto it=_begin; it!=_end; ++it) {
        ret += *it;
    }
    return ret;
}

int main() {
    std::vector<int> vec(3, 3);
    std::cout << sum(vec.begin(), vec.end()) << std::endl;

    int a[] = {3, 3, 3};
    std::cout << sum(a, a+3) << std::endl;
    return 0;
}
