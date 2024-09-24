import six
import sys

sys.modules['sklearn.externals.six'] = six
import mlrose
import numpy as np
import sklearn
import random
import math as mt


def distance(x1, y1, x2, y2):
    return mt.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)


n = 6
# Create list of city coordinates
coords_list = {}
v1 = []
points = {}
for i in range(n):
    coords_list[i] = (random.randint(1, 1000), random.randint(1, 1000))

matrix = []
for i, vi in points.items():
    m1 = []
    for j, vj in points.items():
        if i == j:
            m1.append(0)
        else:
            m1.append(int(distance(vi[0], vi[1], vj[0], vj[1])))
            v1.append([i, j, int(distance(vi[0], vi[1], vj[0], vj[1]))])
    matrix.append(m1.copy())
matrix = [[0, 39, 54, 90, 96, 67], [39, 0, 17, 58, 73, 39], [54, 17, 0, 41, 58, 24], [90, 58, 41, 0, 26, 23],
          [96, 73, 58, 26, 0, 34], [67, 39, 24, 23, 34, 0]]
# Initialize fitness function object using coords_list
fitness_coords = mlrose.TravellingSales(coords=coords_list)

problem_fit = mlrose.TSPOpt(length=n, fitness_fn=fitness_coords,
                            maximize=False)

best_state, best_fitness = mlrose.genetic_alg(problem_fit, mutation_prob=0.2,
                                              max_attempts=1000, random_state=2)

print('The best state found is: ', best_state)

print('The fitness at the best state is: ', best_fitness)
