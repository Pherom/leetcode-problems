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
    public TreeNode RemoveLeafNodes(TreeNode root, int target) {
        TreeNode rec(TreeNode curr, TreeNode parent, int target) {
            if (curr == null) {
                return null;
            }

            curr.left = rec(curr.left, curr, target);
            curr.right = rec(curr.right, curr, target);

            if (curr.left == null && curr.right == null && curr.val == target) {
                return null;
            }

            return curr;
        }

        return rec(root, null, target);
    }
}