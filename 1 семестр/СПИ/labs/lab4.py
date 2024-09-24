import math
from itertools import zip_longest

import numpy as np

def xMatrixConstruct(maX):
    countBits = math.ceil(math.log2(maX))
    xMatr = np.zeros((2 ** countBits, countBits), dtype=np.int64)
    for i in range(2 ** countBits):
        for j in range(countBits):
            xMatr[i][countBits - j - 1] = ((i >> j) & 1)
    return xMatr

def funcMatrixContruct(a, m, maX):
    countYBits = math.ceil(math.log2(m))
    countRow = math.ceil(math.log2(maX))
    funcMatr = np.zeros((2 ** countRow, countYBits), dtype=np.int64)
    for i in range(2 ** countRow):
        for j in range(countYBits):
            funcMatr[i][countYBits - j - 1] = (((a**i%m) >> j) & 1)
    return funcMatr

def yMatrixConstruct(countBits):
    matr = np.zeros((2 ** countBits, countBits), dtype=np.int64)
    for i in range(2 ** countBits):
        for j in range(countBits):
            matr[i][countBits - j - 1] = ((i >> j) & 1)
    return matr

def sqrMod(a, m, maX):
    xMatrix = xMatrixConstruct(maX)
    funcMatrix = funcMatrixContruct(a, m, maX)
    yMatrix = yMatrixConstruct(len(xMatrix[0]) + len(funcMatrix[0]))
    matrXandFunction = np.zeros((len(yMatrix), len(xMatrix[0]) + len(funcMatrix[0])), dtype=np.int64)
    for i in range(len(matrXandFunction)):
        string = ""
        for j in range(len(matrXandFunction[i])):
            if j < len(xMatrix[0]):
                matrXandFunction[i][j] = yMatrix[i][j]
                string += str(yMatrix[i][j])
            else:
                matrXandFunction[i][j] = funcMatrix[int(string, base=2)][j - len(funcMatrix[int(string, base=2)])]^yMatrix[i][j]
    resMatrix = np.zeros((len(yMatrix), len(yMatrix)), dtype=np.int64)
    for i in range(len(yMatrix)):
        stringLine = ""
        stringColumn = ""
        for j in range(len(yMatrix[i])):
            stringLine += str(yMatrix[i][j])
            stringColumn += str(matrXandFunction[i][j])
        resMatrix[int(stringLine, base=2)][int(stringColumn, base=2)] = 1
        print(resMatrix[i])
    print(np.allclose(np.eye(len(resMatrix)), resMatrix.dot(resMatrix.T.conj())))




def calculateBoolfunction(functionMatrix):
    yMas = [0, 1, 0, 1, 0, 1, 0, 1]
    transitionMatrix = [[0, 0], [0, 0], [0, 0], [0, 0], [0, 0], [0, 0], [0, 0], [0, 0]]
    for i in range(len(yMas)):
        transitionTo = 0
        transitionFrom = 0

        res = functionMatrix[int(i / 2)][2] ^ yMas[i]
        if res == 1:
            transitionTo += 1
        if functionMatrix[int(i / 2)][1] == 1:
            transitionTo += 2
        if functionMatrix[int(i / 2)][0] == 1:
            transitionTo += 4

        if yMas[i] == 1:
            transitionFrom += 1
        if functionMatrix[int(i / 2)][1] == 1:
            transitionFrom += 2
        if functionMatrix[int(i / 2)][0] == 1:
            transitionFrom += 4

        transitionMatrix[i][0] = transitionFrom
        transitionMatrix[i][1] = transitionTo

    # print(transitionMatrix)
    n = 8
    resMatrix = [0] * n * n
    for i in range(n):
        resMatrix[n * transitionMatrix[i][0] + transitionMatrix[i][1]] = 1
        for j in range(n):
            print(resMatrix[i * n + j], end=" ")
        print()

    uniMatr = np.zeros((n, n))
    for i in range(len(uniMatr)):
        for j in range(len(uniMatr[i])):
            uniMatr[i][j] = resMatrix[i * n + j]
    print(np.allclose(np.eye(len(uniMatr)), uniMatr.dot(uniMatr.T.conj())))
    boolParallel(resMatrix)
    ejik(resMatrix)


def tensordot(a, b):
    newMatr = np.zeros((len(a) * len(b), len(a[0]) * len(b[0])), dtype=np.int64)
    for i in range(len(a)):
        for j in range(len(a[i])):
            for k in range(len(b)):
                for r in range(len(b[k])):
                    newMatr[i * len(b) + k][j * len(b[k]) + r] = a[i][j] * b[k][r]
    return newMatr

def convertMassToMatrix(mass):
    # n = math.sqrt(len(mass))
    n = int(math.sqrt(len(mass)))
    return list(x for x in zip_longest(*[iter(mass)] * n))


def boolParallel(mass):
    matrix = np.array(convertMassToMatrix(mass))
    indVec = np.array([1, 0, 1, 0, 1, 0, 1, 0])
    resVec = indVec.dot(matrix)
    print(resVec)
    coordVec = []
    for i in range(len(resVec)):
        if resVec[i] == 1:
            binFormat = format(i, 'b')
            coordVec.append('{:{}>{}}'.format(binFormat,'0', '3'))
    print("1/2(|" + coordVec[0] + ">+|" + coordVec[1] + ">+|" + coordVec[2] + ">+|" + coordVec[3] + ">)")

def ejik(mass):
    matrix = np.array(convertMassToMatrix(mass))
    plusMinusVec = np.array([-1, 1, -1, 1, -1, 1, -1, 1])
    resVec = np.array(plusMinusVec.dot(matrix))
    adamar = np.array([[1.0, 1.0], [1.0, -1.0]])
    adMatr = np.array(tensordot(tensordot(adamar, adamar), adamar))
    itogVec = np.array(resVec.dot(adMatr))
    print(itogVec)
    coordVec = []
    for i in range(len(resVec)):
        # if itogVec[i] != 1:
        # костыль
        if itogVec[i] == 1:
            binFormat = format(i, 'b')
            coordVec.append('{:{}>{}}'.format(binFormat, '0', '3'))
    print("(|" + coordVec[0] + ">+|" + coordVec[1] + ">+|" + coordVec[2] + ">+|" + coordVec[3] + ">)")


if __name__ == '__main__':
    print("Part 1:")
    orMatrix = [[0, 0, 1], [0, 1, 1], [1, 0, 1], [1, 1, 1]]
    calculateBoolfunction(orMatrix)
    print("Part 2")
    sqrMod(3, 4, 3)

