/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSameTree(struct TreeNode* first, struct TreeNode* second) {
    if (first == NULL || second == NULL) {
        return first == second;
    }

    return first->val == second->val && isSameTree(first->left, second->left) && isSameTree(first->right, second->right);
}

bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
    if (subRoot == NULL) {
        return true;
    }

    if (root == NULL) {
        return false;
    }

    if (root->val == subRoot->val && isSameTree(root, subRoot)) {
        return true;
    }

    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}