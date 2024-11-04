class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        std::vector<int> f(n);

        for (int i = 0; i < n; i++) f[i] = i;

        for (auto e : edges) {
            int vF = pathCompression(f, f[e[0]]);
            int vW = pathCompression(f, f[e[1]]);

            if (vF != vW) {
                f[vW] = vF;
            }
        }

        pathCompression(f, source);
        pathCompression(f, destination);

        return f[source] == f[destination];
    }

    int pathCompression(std::vector<int>& f, int v) {
        if (f[v] == v) return v;

        f[v] = pathCompression(f, f[v]);

        return f[v];
    }
};
