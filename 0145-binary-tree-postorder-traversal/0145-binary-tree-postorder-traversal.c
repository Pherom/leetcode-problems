/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int leftSize = 0;
    int rightSize = 0;
    int* left = postorderTraversal(root->left, &leftSize);
    int* right = postorderTraversal(root->right, &rightSize);
    int resSize = leftSize + rightSize + 1;

    int* res = (int*)realloc(left, sizeof(int) * resSize);

    if (res == NULL) {
        free(left);
        free(right);
        return NULL;
    }

    if (right != NULL) {
        memcpy(res + leftSize, right, sizeof(int) * rightSize);
    }

    res[resSize - 1] = root->val;
    free(right);

    *returnSize = resSize;
    return res;
}