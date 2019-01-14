// branch.cpp
#include <iostream>

template<bool COND, typename THEN, typename ELSE>
class IF_;

template<typename THEN, typename ELSE>
class IF_<true, THEN, ELSE> {
    public: typedef THEN value_type;
};

template<typename THEN, typename ELSE>
class IF_<false, THEN, ELSE> {
    public: typedef ELSE value_type;
};

int main() {
    const int len = 4;
    IF_<sizeof(short) == len, short,
        IF_<sizeof(int)  == len, int,
            IF_<sizeof(long) == len, long, long long>::value_type>::value_type>::value_type value;
    std::cout << sizeof(value) << std::endl;

    std::conditional<sizeof(short) == len, short, int>::type val;
    std::cout << sizeof(val) << std::endl;
    return 0;
}
