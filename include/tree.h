// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
  struct Node {
    char data;
    std::vector<Node*> children;
    explicit Node(char d) : data(d) {}
  };
  Node* root = nullptr;
  void buildTree(Node* node, const std::vector<char>& elements);
  void collectPermutations(Node* node, std::vector<std::vector<char>>& results,
    std::vector<char>& current) const;
  void findPermByIndex(Node* node, std::vector<char>& result, int index) const;
  void deleteSubtree(Node* node);
  int factorial(int n) const;
 public:
  explicit PMTree(const std::vector<char>& elements);
  ~PMTree();
  void generateAll(std::vector<std::vector<char>>& results) const;
  void getByIndex(std::vector<char>& result, int index) const;
};
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int n);
std::vector<char> getPerm2(PMTree& tree, int n);

#endif  // INCLUDE_TREE_H_
