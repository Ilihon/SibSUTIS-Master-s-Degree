import random
import numpy as np
from math import *


def hadamard_matrix():
    lst = [[1, 1],
           [1, -1]]
    Hadamard = np.array(lst)
    return Hadamard


def generate_qubit():
    a0 = 0
    a1 = 0
    while pow(a0, 2) + pow(a1, 2) != 1:
        a0 = round(random.uniform(0.000, 1.000), 3)
        a1 = round(random.uniform(0.000, 1.000), 3)
        # print(round(a0, 3), round(a1, 3))
    # print(a0 ** 2 + a1 ** 2)
    coef = [a0, a1]
    return np.array(coef)


def qubit_solve(a0):
    rand = round(random.uniform(0.000, 1.000), 3)
    if rand <= pow(a0, 2):
        return np.array([1, 0])
    else:
        return np.array([0, 1])


# 
if __name__ == '__main__':
    coef = generate_qubit()
    a0 = coef[0]
    a1 = coef[1]
    print(f'[a0, a1]: {coef}')
    coef_cp = coef

    # vec0 = np.array([1, 0])
    # vec1 = np.array([0, 1])
    vec = []
    coef = qubit_solve(a0)
    # qubit = vec0 * a0 + vec1 * a1
    print(f'(a): {coef}')

    hadamard = hadamard_matrix()
    # print(f'\nHadamard: {hadamard}')

    b_matrix = np.dot(coef_cp, hadamard)
    b_matrix = b_matrix * (1 / sqrt(2))
    b0 = b_matrix[0]
    b1 = b_matrix[1]
    print(f'\n[b0, b1]: {b_matrix}')
    # a0_ = (1 / sqrt(2)) * (vec0 + vec1)
    # a1_ = (1 / sqrt(2)) * (vec0 - vec1)
    b_matrix = qubit_solve(b0)
    # qubit_ = b0 * a0_ + b1 * a1_
    print(f'(=b): {b_matrix}')
