class Solution:
    def dfs(
        self,
        graph: list[list[int]],
        v: int,
        target: int,
        marked: list[bool],
        paths: list[list[int]],
        current_path: list[list[int]],
    ) -> None:
        marked[v] = True
        current_path.append(v)

        for w in graph[v]:
            if w == target:
                final_path = current_path.copy()
                final_path.append(w)
                paths.append(final_path)
                continue

            if not marked[w]:
                self.dfs(graph, w, target, marked.copy(), paths, current_path.copy())

    def allPathsSourceTarget(self, graph: list[list[int]]) -> list[list[int]]:
        paths: list[list[int]] = []
        self.dfs(graph, 0, len(graph) - 1, [False] * len(graph), paths, [])
        return paths
