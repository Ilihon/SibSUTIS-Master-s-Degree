import math
from lab2 import *


def xMatrix_gen(x):
    bits_count = math.ceil(math.log2(x))
    print(f"Bits count: {bits_count}")
    matrix = np.zeros((2 ** bits_count, bits_count), dtype=np.int64)
    for i in range(2 ** bits_count):
        for j in range(bits_count):
            # print(i, j, i >> j, (i >> j) & 1)
            matrix[i][bits_count - j - 1] = ((i >> j) & 1)
    print(f"X matrix: \n{matrix}\n")
    return matrix


def funcMatrix_gen(a, x, m):
    xBits_count = math.ceil(math.log2(x))
    mBits_count = math.ceil(math.log2(x))
    print(f"Bits count: {xBits_count}")
    matrix = np.zeros((2 ** xBits_count, mBits_count), dtype=np.int64)
    for i in range(2 ** xBits_count):
        for j in range(mBits_count):
            # function a^x mod m
            matrix[i][mBits_count - j - 1] = (((a ** i % m) >> j) & 1)
    print(f"Func matrix: \n{matrix}\n")
    return matrix


def yMatrix_gen(bits_count):
    print(f"Bits count: {bits_count}")
    matrix = np.zeros((2 ** bits_count, bits_count), dtype=np.int64)
    for i in range(2 ** bits_count):
        for j in range(bits_count):
            matrix[i][bits_count - j - 1] = ((i >> j) & 1)
    print(f"Y matrix: \n{matrix}\n")
    return matrix


def yMatrix_transform(y_matrix, func_matrix, x_matrixLen):
    y_matrix_transformed = y_matrix.copy()
    for i in range(len(y_matrix_transformed)):
        binary_string = ""
        for j in range(x_matrixLen):
            binary_string += str(y_matrix_transformed[i][j])
        decimal = int(binary_string, 2)
        # print(f"{binary_string} - {decimal}")
        for j in range(x_matrixLen, len(y_matrix_transformed[i])):
            y_matrix_transformed[i][j] = y_matrix_transformed[i][j] ^ func_matrix[decimal][j-x_matrixLen]
    print(f"Y matrix transformed: \n{y_matrix_transformed}\n")
    # print(f"Y matrix: \n{y_matrix}\n")
    return y_matrix_transformed


def F_Matrix_gen(y_matrix, y_matrix_transformed):

    F_matrix = np.zeros((len(y_matrix), len(y_matrix_transformed)), dtype=np.int64)
    # print(f"{y_matrix}\n\n{y_matrix_transformed}")

    for i in range(len(y_matrix)):
        binary_string_i = ""
        binary_string_j = ""
        for j in range(len(y_matrix[i])):
            binary_string_i += str(y_matrix[i][j])
            binary_string_j += str(y_matrix_transformed[i][j])

        decimal_i = int(binary_string_i, 2)
        decimal_j = int(binary_string_j, 2)
        print(f"{binary_string_i} - {decimal_i}\t {binary_string_j} - {decimal_j}")
        F_matrix[decimal_i][decimal_j] = 1

    # print(f"F matrix : \n{F_matrix}\n")
    return F_matrix


def quantum_computation(a, x, m):

    # lines = (int(x / 2) + (x % 2 if x % 2 == 0 else (x % 2) + 1))ы
    # print(f"Lines count: {lines}")
    x_matrix = xMatrix_gen(x)
    func_matrix = funcMatrix_gen(a, x, m)
    y_matrix = yMatrix_gen(len(x_matrix[0]) + len(func_matrix[0]))
    y_matrix_transformed = yMatrix_transform(y_matrix, func_matrix, len(x_matrix[0]))
    F_matrix = F_Matrix_gen(y_matrix, y_matrix_transformed)
    print(f"Result: \n{F_matrix}\n")


if __name__ == '__main__':
    print("Enter a:")
    a = int(input())
    print("Enter x:")
    x = int(input())
    print("Enter m:")
    m = int(input())

    quantum_computation(a, x, m)

