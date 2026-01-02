/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
typedef struct TreeNode TreeNode;

TreeNode* removeLeafNodes(TreeNode* root, int target) {
    if (root == NULL) {
        return NULL;
    }

    root->left = removeLeafNodes(root->left, target);
    root->right = removeLeafNodes(root->right, target);

    if (root->val == target && root->left == NULL && root->right == NULL) {
        // free(root);
        return NULL;
    }

    return root;
}