/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left;
 *     public TreeNode right;
 *     public TreeNode(int val=0, TreeNode left=null, TreeNode right=null) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
public class Solution {
    private int DiameterOfBinaryTreeRec(TreeNode root, out int depth) {
        if (root == null) {
            depth = -1;
            return -1;
        }

        int leftDepth;
        int rightDepth;

        int leftDiameter = DiameterOfBinaryTreeRec(root.left, out leftDepth);
        int rightDiameter = DiameterOfBinaryTreeRec(root.right, out rightDepth);

        depth = 1 + Math.Max(leftDepth, rightDepth);
        return Math.Max(leftDiameter, Math.Max(rightDiameter, 2 + leftDepth + rightDepth));
    }

    public int DiameterOfBinaryTree(TreeNode root) {
        int diameter;
        return DiameterOfBinaryTreeRec(root, out diameter);
    }
}