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
    bool isSametree(TreeNode* first, TreeNode* second) {
        if (first == nullptr || second == nullptr) {
            return first == second;
        }

        return first->val == second->val && isSametree(first->left, second->left) && isSametree(first->right, second->right);;
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