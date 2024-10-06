class BSTIterator {
    private TreeNode r;
    private Deque<Integer> q;

    public BSTIterator(TreeNode root) {
        this.r = root;
        this.q = new ArrayDeque<>();
        this.inOrder(r);
    }
    
    public int next() {
        return this.q.removeFirst();
    }
    
    public boolean hasNext() {
        return !this.q.isEmpty();
    }

    private void inOrder(TreeNode c) {
        if (c == null) return;
        this.inOrder(c.left);
        this.q.addLast(c.val);
        this.inOrder(c.right);
    }
}
