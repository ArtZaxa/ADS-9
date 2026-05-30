// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <vector>
#include  "tree.h"

static void collectPerms(PMTree::Node* node, std::vector<char>& path,
                        std::vector<std::vector<char>>& out) {
    if (!node) return;

    if (node->children.empty()) {
        out.push_back(path);
        return;
    }

    for (auto* child : node->children) {
        path.push_back(child->value);
        collectPerms(child, path, out);
        path.pop_back();
    }
}
std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    collectPerms(tree.getRoot(), path, result);
    return result;
}
static bool collectNthPerm(PMTree::Node* node, std::vector<char>& path,
                            int& num, std::vector<char>& result) {
    if (!node) return false;

    if (node->children.empty()) {
        --num;
        if (num == 0) {
            result = path;
            return true;
        }
        return false;
    }

    for (auto* child : node->children) {
        path.push_back(child->value);
        if (collectNthPerm(child, path, num, result))
            return true;
        path.pop_back();
    }

    return false;
}
std::vector<char> getPerm1(PMTree& tree, int num) {
    if (num <= 0 || static_cast<std::size_t>(num) > tree.getRoot()->leavesCount)
        return {};

    std::vector<char> path;
    std::vector<char> result;
    collectNthPerm(tree.getRoot(), path, num, result);
    return result;
}
std::vector<char> getPerm2(PMTree& tree, int num) {
    if (num <= 0) return {};
    PMTree::Node* current = tree.getRoot();
    if (!current) return {};
    if (static_cast<std::size_t>(num) > current->leavesCount) return {};

    std::vector<char> result;
    std::size_t index = static_cast<std::size_t>(num - 1);

    while (!current->children.empty()) {
        std::size_t blockSize = current->children[0]->leavesCount;
        std::size_t childIndex = index / blockSize;
        if (childIndex >= current->children.size()) return {};
        current = current->children[childIndex];
        result.push_back(current->value);
        index %= blockSize;
    }

    return result;
}
