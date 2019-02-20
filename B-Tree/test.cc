#include <iostream>
#include <vector>
#include <algorithm>
#include "btree.hpp"

int main() {
    BTree<int> btree(3);
    for (int i=0; i<100; ++i) {
        btree.insert(i);
    }

    std::vector<int> treeData;
    btree.traverse(treeData);
    for (auto x: treeData)
        std::cout << x << "\t";
    std::cout << std::endl;
    return 0;
}
