class Solution {
  public double myPow(double x, int n) {
    if (n == -2147483648 || n == 2147483647)
      return Math.abs(x) == 1 ? (x == 1 ? 1 : (n < 0 ? 1 : -1)) : 0;

    double m = 1.0;

    for (int i = Math.abs(n); i > 0; i--) {
      m *= n > 0 ? x : 1 / x;
    }

    return m;
  }
}
