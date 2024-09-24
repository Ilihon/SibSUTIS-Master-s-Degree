import pandas as pd


class Graph:
    def __init__(self, graph, source, sink):
        self.graph = graph
        self.vertex_count = len(graph)
        self.start = source
        self.end = sink
        self.pathes = []


def find_path_BFS(g, parent):
    visited = [False] * g.vertex_count
    queue = [g.start]
    visited[g.start] = True

    while queue:
        u = queue.pop(0)
        # print(g.graph[u])
        for ind, val in enumerate(g.graph[u]):
            if visited[ind] == False and val > 0:
                queue.append(ind)
                visited[ind] = True
                parent[ind] = u

    if visited[g.end]:
        return True
    else:
        return False


def ford_fulkerson(g):
    parent = [-1] * g.vertex_count
    max_flow = 0

    while find_path_BFS(g, parent):

        path_history = [g.end]

        path_flow = float("Inf")
        s = g.end
        while s != source:
            path_flow = min(path_flow, g.graph[parent[s]][s])
            s = parent[s]
            path_history = [s] + path_history
            # print(s)

        g.pathes.append(path_history)

        max_flow += path_flow

        v = g.end
        while (v != source):
            u = parent[v]
            g.graph[u][v] -= path_flow
            g.graph[v][u] += path_flow
            v = parent[v]

    return max_flow


if __name__ == "__main__":
    graph = []

    with open('ford_falkerson_flow3.in', 'r') as file:
        for line in file.readlines():
            rows = list(map(int, line.split()))
            graph.append(rows)

    print("Граф:")
    print(pd.DataFrame(graph), "\n")

    source = 0
    sink = 5  # 1ый файл
    # sink = 3 # 2ой файл

    g = Graph(graph, source, sink)

    print("Максимальный поток: %d " % ford_fulkerson(g))
    print("Найденные пути: ")
    for path in g.pathes:
        print(path)

    print("Граф:")
    print(pd.DataFrame(graph), "\n")
