#include <iostream>
#include <vector>
#include <algorithm>
#include "btree.hpp"

int main() {
    std::vector<int> nums;
    for (int i=0; i<100; ++i) {
        nums.push_back(i);
    }
    srand(0);
    for (int i=0; i<100; ++i) {
        int j = rand() % 100;
        std::swap(nums[i], nums[j]);
    }
    BTree<int> btree(3);
    for (int i=0; i<100; ++i) {
        btree.insert(nums[i]);
    }

    std::vector<int> treeData;
    btree.traverse(treeData);
    for (auto x: treeData)
        std::cout << x << "\t";
    std::cout << std::endl;
    return 0;
}
