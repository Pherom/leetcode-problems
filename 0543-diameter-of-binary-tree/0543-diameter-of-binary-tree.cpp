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
    int diameterOfBinaryTreeRec(TreeNode* root, int& longestPathFromRoot) {
        if (root == nullptr) {
            longestPathFromRoot = -1;
            return -1;
        }

        int lpLeft = -1;
        int lpRight = -1;
        int dLeft = diameterOfBinaryTreeRec(root->left, lpLeft);
        int dRight = diameterOfBinaryTreeRec(root->right, lpRight);

        longestPathFromRoot = 1 + std::max(lpLeft, lpRight);
        return std::max(dLeft, std::max(dRight, 2 + lpLeft + lpRight));
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        int longestPathFromRoot = -1;
        return diameterOfBinaryTreeRec(root, longestPathFromRoot);
    }
};