/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    bool isIdenticalTree(TreeNode* first, TreeNode* second) {
        if (first == nullptr || second == nullptr) {
            return first == second;
        }

        return first->val == second->val && isIdenticalTree(first->left, second->left) && isIdenticalTree(first->right, second->right);;
    }

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (subRoot == nullptr) {
            return true;
        }

        if (root == nullptr) {
            return false;
        }

        return isIdenticalTree(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};