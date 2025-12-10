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

    if (root->val < key) {
        root->right = deleteNode(root->right, key);
        return root;
    }

    if (root->val > key) {
        root->left = deleteNode(root->left, key);
        return root;
    }

    struct TreeNode* prev = root;
    struct TreeNode* curr = root->right;

    if (curr == NULL) {
        struct TreeNode* temp = root->left;
        free(root);
        return temp;
    }

    while (curr->left != NULL) {
        prev = curr;
        curr = curr->left;
    }

    root->val = curr->val;

    if (prev->left == curr) {
        prev->left = curr->right;
    } else {
        prev->right = curr->right;
    }

    free(curr);
    return root;
}