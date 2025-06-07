// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <vector>
#include <algorithm>
#include  "tree.h"

void PMTree::buildTree(Node* node, const std::vector<char>& elements) {
    if (elements.empty()) return;
    for (size_t i = 0; i < elements.size(); ++i) {
        Node* child = new Node(elements[i]);
        node->children.push_back(child);
        std::vector<char> remaining = elements;
        remaining.erase(remaining.begin() + i);
        buildTree(child, remaining);
    }
}
void PMTree::collectPermutations(Node* node,
    std::vector<std::vector<char>>& results, std::vector<char>& current) const {
    if (!node) return;
    if (node->data != '\0') {
        current.push_back(node->data);
    }
    if (node->children.empty()) {
        results.push_back(current);
    } else {
        for (Node* child : node->children) {
            collectPermutations(child, results, current);
        }
    }
    if (!current.empty()) {
        current.pop_back();
    }
}
void PMTree::findPermByIndex(Node* node,
    std::vector<char>& result, int index) const {
    if (!node || node->children.empty()) return;
    int count = node->children.size();
    int fact = factorial(count - 1);
    int childIndex = index / fact;
    if (childIndex >= count) return;
    Node* selected = node->children[childIndex];
    result.push_back(selected->data);
    findPermByIndex(selected, result, index % fact);
}
void PMTree::deleteSubtree(Node* node) {
    if (!node) return;
    for (Node* child : node->children) {
        deleteSubtree(child);
    }
    delete node;
}
int PMTree::factorial(int n) const {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
PMTree::PMTree(const std::vector<char>& elements) {
    root = new Node('\0');
    buildTree(root, elements);
}
PMTree::~PMTree() {
    deleteSubtree(root);
}
void PMTree::generateAll(std::vector<std::vector<char>>& results) {
    std::vector<char> current;
    collectPermutations(root, results, current);
}
void PMTree::getByIndex(std::vector<char>& result, int index) {
    if (index <= 0) return;
    findPermByIndex(root, result, index - 1);
}
std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> results;
    tree.generateAll(results);
    return results;
}
std::vector<char> getPerm1(PMTree& tree, int index) {
    auto allPerms = getAllPerms(tree);
    if (index > 0 && static_cast<size_t>(index) <= allPerms.size()) {
        return allPerms[index - 1];
    }
    return {};
}
std::vector<char> getPerm2(PMTree& tree, int index) {
    std::vector<char> result;
    tree.getByIndex(result, index);
    return result;
}
