// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <iostream>
#include <vector>
#include  "tree.h"

void PermutationGenerator::buildTreeStructure(TreeNode* node, const std::vector<char>& elements) {
    if (elements.empty()) {
      return;
    }
    for (size_t i = 0; i < elements.size(); ++i) {
      TreeNode* child = new TreeNode(elements[i]);
      node->children.push_back(child);
      std::vector<char> remaining = elements;
      remaining.erase(remaining.begin() + i);
      buildTreeStructure(child, remaining);
    }
}
void PermutationGenerator::collectPermutations(TreeNode* node, std::vector<std::string>& results, std::string& current) const {
    if (!node) {
      return;
    }
    if (node->value != '\0') {
      current.push_back(node->value);
    }
    if (node->children.empty()) {
      results.push_back(current);
    } else {
      for (TreeNode* child : node->children) {
        collectPermutations(child, results, current);
      }
    }
    if (!current.empty()) {
      current.pop_back();
    }
}
void PermutationGenerator::findPermutationByIndex(TreeNode* node, std::string& result, int index) const {
  if (!node || node->children.empty()) {
    return;
  }
  int count = node->children.size();
  int fact = calculateFactorial(count - 1);
  int childIndex = index / fact;
  if (childIndex >= count) {
    return;
  }
  TreeNode* selected = node->children[childIndex];
  result.push_back(selected->value);
  findPermutationByIndex(selected, result, index % fact);
}
void PermutationGenerator::cleanupTree(TreeNode* node) {
  if (!node) {
  return;
  }
  for (TreeNode* child : node->children) {
    cleanupTree(child);
  }
  delete node;
}
int PermutationGenerator::calculateFactorial(int n) const {
  return (n <= 1) ? 1 : n * calculateFactorial(n - 1);
}
PermutationGenerator::PermutationGenerator(const std::vector<char>& elements) {
  root = new TreeNode('\0');
  buildTreeStructure(root, elements);
}
PermutationGenerator::~PermutationGenerator() {
  cleanupTree(root);
}
void PermutationGenerator::getAllPermutations(std::vector<std::string>& results) const {
  std::string current;
  collectPermutations(root, results, current);
}
void PermutationGenerator::getPermutationByIndex(std::string& result, int index) const {
  if (index <= 0) {
    return;
  }
  findPermutationByIndex(root, result, index - 1);
}
std::vector<std::string> generateAllPermutations(PermutationGenerator& generator) {
  std::vector<std::string> results;
  generator.getAllPermutations(results);
  return results;
}
std::string getPermutationMethod1(PermutationGenerator& generator, int index) {
  auto allPerms = generateAllPermutations(generator);
  if (index > 0 && index <= allPerms.size()) {
    return allPerms[index - 1];
  }
  return "";
}
std::string getPermutationMethod2(PermutationGenerator& generator, int index) {
  std::string result;
  generator.getPermutationByIndex(result, index);
  return result;
}
