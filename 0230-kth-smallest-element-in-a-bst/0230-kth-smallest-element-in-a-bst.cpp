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
    int kthSmallestRec(TreeNode* root, int k, int& nodeCount) {
        if (root == nullptr) {
            nodeCount = 0;
            return -1;
        }

        int leftNodeCount = 0;
        int rightNodeCount = 0;
        int smallestLeft = kthSmallestRec(root->left, k, leftNodeCount);
        int smallestRight = kthSmallestRec(root->right, k - leftNodeCount - 1, rightNodeCount);

        nodeCount = leftNodeCount + rightNodeCount + 1;

        if (smallestLeft != -1) {
            return smallestLeft;
        }

        if (leftNodeCount == k - 1) {
            return root->val;
        }

        return smallestRight;
    }

public:
    int kthSmallest(TreeNode* root, int k) {
        int nodeCount = 0;
        return kthSmallestRec(root, k, nodeCount);
    }
};