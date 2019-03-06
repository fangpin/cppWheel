#include <iostream>
#include <vector>
#include <algorithm>
#include "btree.hpp"

int main() {
    BTree<int> btree(2);
    for (int i=0; i<1000; ++i) {
        btree.insert(i);
    }

    for (int i=500; i<1000; ++i) {
        btree.erase(i);
    }

    std::vector<int> treeData;
    btree.traverse(treeData);
    for (auto x: treeData)
        std::cout << x << "\t";
    std::cout << std::endl;
    return 0;
}
