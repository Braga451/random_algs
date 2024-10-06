class LRUCache {
  private Node priorityList = null; // Point to the head of list, that is, the LRU element
  private final Map<Integer, Node> nodeMapping = new HashMap<>();
  private final Map<Integer, Integer> caching = new HashMap<>();
  private int capacity;

  public LRUCache(int capacity) {
    this.capacity = capacity;
  }

  public int get(int key) {
    Integer v = this.caching.get(key);
    if (v == null)
      return -1;
    this.updateLastUsedElement(key);
    return v;
  }

  public void put(int key, int value) {
    if (caching.get(key) == null) {
      Node pKey = new Node(key);
      nodeMapping.put(key, pKey);

      if (this.caching.size() == capacity) {
        this.caching.remove(this.priorityList.val);
        this.removeElement(this.priorityList.val);
      }
    }
    this.updateLastUsedElement(key);
    this.caching.put(key, value);
  }

  private void removeElement(int k) {
    Node n = nodeMapping.get(k);

    n.prev.next = n.next;
    n.next.prev = n.prev;
    this.priorityList = n.next;
  }

  private void updateLastUsedElement(int k) {
    Node n = nodeMapping.get(k);

    if (this.priorityList == null || this.capacity == 1) {
      n.next = n;
      n.prev = n;
      this.priorityList = n;
      return;
    }

    if (n == this.priorityList.prev)
      return;
    if (n == this.priorityList) {
      this.priorityList = this.priorityList.next;
      return;
    }

    Node head = this.priorityList,
        prev = n.prev,
        next = n.next;

    if (prev != null) {
      prev.next = next;
    }

    if (next != null) {
      next.prev = prev;
    }

    n.next = head;
    n.prev = head.prev;
    head.prev.next = n;
    head.prev = n;
  }

  private class Node {
    public Node next;
    public Node prev;
    public int val;

    public Node(int val) {
      this.val = val;
    }

    /*
     * public void printList() {
     * Node tmp = this;
     * 
     * do {
     * System.out.print(tmp.val + " ");
     * tmp = tmp.next;
     * }while(tmp != this);
     * System.out.println("");
     * }
     */
  }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
