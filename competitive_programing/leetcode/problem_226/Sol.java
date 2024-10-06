class Solution {
  public TreeNode invertTree(TreeNode root) {
    bfsInvert(root);
    return root;
  }

  private void bfsInvert(TreeNode n) {
    Stack<TreeNode> s = new Stack<>();

    s.push(n);

    while (!s.empty()) {
      TreeNode r = s.pop();

      if (r == null)
        continue;

      TreeNode tmp = null;

      if (r.left != null)
        s.push(r.left);

      if (r.right != null)
        s.push(r.right);

      tmp = r.right;
      r.right = r.left;
      r.left = tmp;
    }
  }
}
