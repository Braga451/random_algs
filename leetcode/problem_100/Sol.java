class Solution {
  public boolean isSameTree(TreeNode p, TreeNode q) {
    List<Integer> l1 = new ArrayList<>(),
        l2 = new ArrayList<>();
    inOrder(p, l1);
    inOrder(q, l2);

    if (l1.size() != l2.size())
      return false;

    for (int i = 0; i < l1.size(); i++)
      if (l1.get(i) != l2.get(i)) {
        if (l1.get(i) != null && l2.get(i) != null && l1.get(i) - l2.get(i) == 0)
          continue;
        return false;
      }

    l1 = null;
    l2 = null;

    return true;
  }

  public void inOrder(TreeNode n, List<Integer> l) {
    l.add(n == null ? null : n.val);
    if (n == null)
      return;
    inOrder(n.left, l);
    inOrder(n.right, l);
  }
}
