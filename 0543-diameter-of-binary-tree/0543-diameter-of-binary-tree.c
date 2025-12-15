/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define MAX(first, second) ( ( first ) > ( second ) ? ( first ) : ( second ) )

int diameterOfBinaryTreeRec(struct TreeNode *root, int *longestPathFromRoot) {
    if (root == NULL) {
        *longestPathFromRoot = -1;
        return -1;
    }

    int longestFromLeft = -1;
    int longestFromRight = -1;

    int diameterLeft = diameterOfBinaryTreeRec(root->left, &longestFromLeft);
    int diameterRight = diameterOfBinaryTreeRec(root->right, &longestFromRight);
    int throughRoot = longestFromLeft + longestFromRight + 2;

    *longestPathFromRoot = 1 + MAX(longestFromLeft, longestFromRight);
    return MAX(throughRoot, MAX(diameterLeft, diameterRight));
}

int diameterOfBinaryTree(struct TreeNode* root) {
    int longestPathFromRoot = -1;
    return diameterOfBinaryTreeRec(root, &longestPathFromRoot);
}