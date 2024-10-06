class Solution:
    def __init__(self) -> None:
        self.__c = 0

    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        adjList: dict[int, list[int]] = dict.fromkeys(range(numCourses), None)
        dt: list[int] = [-1 for i in range(numCourses)]
        df: list[int] = [-1 for i in range(numCourses)]
        hasReturnEdge: list[bool] = [False]

        for edge in prerequisites:
            if edge[0] == edge[1]:
                return False

            if adjList[edge[0]] is None:
                adjList[edge[0]] = []

            adjList[edge[0]].append(edge[1])

        marked: list[bool] = [False for i in range(numCourses)]

        for i in range(numCourses):
            if not marked[i]:
                self.__dfs(i, adjList, dt, marked, hasReturnEdge, df)
                if hasReturnEdge[0]:
                    return False

        return not hasReturnEdge[0]

    def __dfs(
        self,
        v: int,
        adjList: dict[int, list[int]],
        discoveredTime: list[int],
        marked: list[int],
        hasReturnEdge: list[bool],
        finishedTime: list[int],
    ) -> None:
        marked[v] = True
        self.__c += 1
        discoveredTime[v] = self.__c

        if adjList[v] is not None:
            for w in adjList[v]:
                if not marked[w]:
                    self.__dfs(
                        w, adjList, discoveredTime, marked, hasReturnEdge, finishedTime
                    )

                elif marked[w] and finishedTime[w] == -1:
                    hasReturnEdge[0] = True
                    return

        self.__c += 1
        finishedTime[v] = self.__c
