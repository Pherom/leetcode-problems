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
    bool isSametree(TreeNode* root, TreeNode* subRoot) {
        if (root == nullptr && subRoot == nullptr) {
            return true;
        }

        if (root == nullptr) {
            return false;
        }

        if (subRoot == nullptr) {
            return false;
        }

        return root->val == subRoot->val && isSametree(root->left, subRoot->left) && isSametree(root->right, subRoot->right);;
    }

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        bool same = false;
        bool left = false;
        bool right = false;

        if (root->val == subRoot->val) {
            same = isSametree(root, subRoot);
        }

        if (!same && root->left != nullptr) {
            left = isSubtree(root->left, subRoot);
        }

        if (!same && !left && root->right != nullptr) {
            right = isSubtree(root->right, subRoot);
        }

        return same || left || right;
    }
};