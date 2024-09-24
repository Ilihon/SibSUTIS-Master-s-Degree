import random
import matplotlib.pyplot as plt
import networkx as nx
import math as mt
from bitarray import bitarray


def distance(x1, y1, x2, y2):
    return mt.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)


INF = 2 ** 31 - 1

# random.seed(1)

n = 6

v1 = []
points = {}
for i in range(n):
    points[i] = (random.randint(1, 1000), random.randint(1, 1000))

input_matrix = []
for i, vi in points.items():
    m1 = []
    for j, vj in points.items():
        if i == j:
            m1.append(INF)
        else:
            m1.append(int(distance(vi[0], vi[1], vj[0], vj[1])))
            v1.append([i, j, int(distance(vi[0], vi[1], vj[0], vj[1]))])
    input_matrix.append(m1.copy())

plt.figure(figsize=(8, 8))

graph = nx.Graph()
graph.add_nodes_from(points)

# Добавляем дуги в граф
for i in v1:
    graph.add_edge(i[0], i[1], weight=i[2])


# -----------------------------------------------------------------
def calc_next(m, s, n, src):
    min = INF
    best = 255
    for i, val in enumerate(s.tolist()):
        if val == 0:
            s0 = s.copy()
            s0[i] = 1
            if n > 2:
                sum = m[src][i]
                r = calc_next(m, s0, n - 1, i)
                sum = sum + r[0]
                temp = r[1]
            else:
                for j, val_j in enumerate(s0.tolist()):
                    if val_j == 0:
                        break
                temp = [j]
                sum = m[src][i] + m[i][j] + m[j][len(m) - 1]
            temp.append(i)
            if sum < min:
                min = sum
                best = i
                temp2 = temp.copy()
    return [min, temp2]


# -----------------------------------------------------------------
s = bitarray(n - 1)
s.setall(0)
r = calc_next(input_matrix, s, n - 1, n - 1)
r[1].append(n - 1)

print(input_matrix)
print('min:', r[0])
print(r[1])

d = []
s = r[1]
for i, v in enumerate(s):
    d.append([int(s[i - 1]), int(s[i])])

# Рисуем всё древо
nx.draw(graph, points, width=1, edge_color="#A0A0A0", with_labels=True)
nx.draw(graph, points, width=2, edge_color="blue", edgelist=d, style='dashed')
plt.show()
