/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    if (root->val != key) {
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }

    if (root->right == NULL) {
        struct TreeNode* left = root->left;
        free(root);
        return left;
    }

    struct TreeNode* prev = root;
    struct TreeNode* curr = root->right;

    while (curr->left != NULL) {
        prev = curr;
        curr = curr->left;
    }

    root->val = curr->val;

    if (prev->right == curr) {
        prev->right = curr->right;
    } else {
        prev->left = curr->right;
    }

    free(curr);
    return root;
}