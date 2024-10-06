class Solution {
  public int longestConsecutive(int[] nums) {
    Map<Integer, Father> f = new HashMap<>();

    for (int n : nums) {
      f.put(n, new Father(n));
      if (f.get(n - 1) != null) {
        f.put(n, f.get(n - 1));
      }
      if (f.get(n + 1) != null) {
        f.put(n + 1, f.get(n));
      }
    }

    int major = 0;
    Map<Integer, Integer> c = new HashMap<>();
    for (int n : f.keySet()) {
      recUpdate(f, n);

      if (c.get(f.get(n).getV()) == null) {
        c.put(f.get(n).getV(), 0);
      }

      c.put(f.get(n).getV(), c.get(f.get(n).getV()) + 1);

      if (c.get(f.get(n).getV()) > major) {
        major = c.get(f.get(n).getV());
      }
    }

    return major;
  }

  private int recUpdate(Map<Integer, Father> f, int n) {
    if (f.get(n).getV() == n)
      return n;
    f.put(n, f.get(recUpdate(f, f.get(n).getV())));
    return n;
  }

  private class Father {
    private int v;

    public Father(int v) {
      this.v = v;
    }

    public int getV() {
      return v;
    }

    @Override
    public String toString() {
      return String.format("%d", this.v);
    }

  }
}
