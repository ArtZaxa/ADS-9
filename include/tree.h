// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

class PMTree {
 public:
    struct Node {
        char value;
        std::vector<Node*> children;
        std::size_t leavesCount;

        explicit Node(char value)
            : value(value), leavesCount(0) {
        }
    };

 private:
    Node* root_;

    static Node* buildNode(char value, const std::vector<char>& available) {
        Node* node = new Node(value);
        if (available.empty()) {
            node->leavesCount = 1;
            return node;
        }

        node->leavesCount = 0;
        for (std::size_t i = 0; i < available.size(); ++i) {
            std::vector<char> next;
            next.reserve(available.size() - 1);
            for (std::size_t j = 0; j < available.size(); ++j) {
                if (i != j) next.push_back(available[j]);
            }
            Node* child = buildNode(available[i], next);
            node->children.push_back(child);
            node->leavesCount += child->leavesCount;
        }
        return node;
    }

    static void deleteNode(Node* node) {
        if (!node) return;
        for (Node* child : node->children) {
            deleteNode(child);
        }
        delete node;
    }

 public:
    explicit PMTree(std::vector<char> input) {
        std::sort(input.begin(), input.end());
        root_ = buildNode('\0', input);
    }

    ~PMTree() { deleteNode(root_); }

    Node* getRoot() const { return root_; }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);


#endif  // INCLUDE_TREE_H_
