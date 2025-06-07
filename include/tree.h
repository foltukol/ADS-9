// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <string>

class PermutationGenerator {
  struct TreeNode {
    char value;
    std::vector<TreeNode*> children;
    TreeNode(char val) : value(val) {}
  };
  TreeNode* root = nullptr;
  void buildTreeStructure(TreeNode* node, const std::vector<char>& elements);
  void collectPermutations(TreeNode* node, std::vector<std::string>& results, std::string& current) const;
  void findPermutationByIndex(TreeNode* node, std::string& result, int index) const;
  void cleanupTree(TreeNode* node);
  int calculateFactorial(int n) const;
 public:
  explicit PermutationGenerator(const std::vector<char>& elements);
  ~PermutationGenerator();
  void initialize();
  void getAllPermutations(std::vector<std::string>& results) const;
  void getPermutationByIndex(std::string& result, int index) const;
};
std::vector<std::string> generateAllPermutations(PermutationGenerator& generator);
std::string getPermutationMethod1(PermutationGenerator& generator, int index);
std::string getPermutationMethod2(PermutationGenerator& generator, int index);

#endif  // INCLUDE_TREE_H_
