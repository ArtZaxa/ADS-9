// Copyright 2022 NNTU-CS
#include <time.h>
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include "tree.h"

void printPerm(const std::vector<char>& perm) {
    if (perm.empty()) {
        std::cout << "empty";
        return;
    }

    for (char c : perm) {
        std::cout << c;
    }
}

int main() {
    std::vector<char> in = { '0', '1', '2', '3', '4', '5', '6', '7', '8'};
    PMTree tree(in);
    auto f1_st = std::chrono::steady_clock::now();
    const std::vector<std::vector<char>>& perms = getAllPerms(tree);
    auto f1_en = std::chrono::steady_clock::now();
    std::cout << "func 1 rand permutations:\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, perms.size());
    int n = distrib(gen);
    std::cout << n+1 << ": ";
    printPerm(perms[n]);
    std::cout << '\n';
    std::cout << (f1_en - f1_st).count()  << " -- time" << std::endl;
    std::cout << "\ngetPerm1 examples:\n";
    auto f2_st = std::chrono::steady_clock::now();
    std::vector<char> p2 = getPerm1(tree, n);
    auto f2_en = std::chrono::steady_clock::now();
    std::cout << (f2_en - f2_st).count() << std::endl;

    std::cout << "getPerm1(tree,"  << n+1 << ") = ";
    printPerm(p2);
    std::cout << '\n';

    std::cout << "\ngetPerm2 examples:\n";
    auto f3_st = std::chrono::steady_clock::now();
    std::vector<char> q3 = getPerm2(tree, n);
    auto f3_en = std::chrono::steady_clock::now();
    std::cout << (f3_en - f3_st).count() << std::endl;

    std::cout << "getPerm2(tree," << n+1 << ") = ";
    printPerm(q3);
    std::cout << '\n';
    return 0;
}
