import random
import numpy as np
from statsmodels.graphics.tsaplots import plot_acf
import matplotlib.pyplot as plt

n = 10
size = 10000
show_size = 30
shift = 0


def normalization(matr, rowsum):
    for i in range(n):
        rowSum2 = 0
        for j in range(n):
            if j == n - 1:
                matr[i][j] = 1 - rowSum2
                break

            matr[i][j] = matr[i][j] / rowsum[i]
            rowSum2 += matr[i][j]
    return matr


def check_matrix(matr):
    print('Проверка два-стохастичности матрицы:')
    rowMultySum = [round(sum(e), 1) for e in matr]
    print('По строкам: ', rowMultySum)

    colsum = []
    for column in range(len(matr[0])):
        t = 0
        for row in matr:
            t += row[column]
        colsum.append(round(t, 1))
    print('По столбцам:', colsum)


def Chain(matr):
    partLen = 1 / n
    selectedNodes = []
    freq = [0 for j in range(n)]
    generatedset = []

    currentNode = 0
    freq[currentNode] += 1
    selectedNodes.append(currentNode)

    beginborder = currentNode * partLen
    endborder = beginborder + partLen
    generatedset.append(random.uniform(beginborder, endborder))

    for i in range(size - 1):
        nextNodeProb = random.uniform(0, 1)
        cumulativeProb = 0
        for j in range(len(matr[currentNode])):
            cumulativeProb += matr[currentNode][j]

            if j == len(matr[currentNode]) - 1:
                cumulativeProb = 1

            if nextNodeProb <= cumulativeProb:
                currentNode = j
                freq[currentNode] += 1
                selectedNodes.append(currentNode)

                beginborder = currentNode * partLen
                endborder = beginborder + partLen
                generatedset.append(random.uniform(beginborder, endborder))
                break
    print()

    nodesFreq = []
    for i in freq:
        nodesFreq.append(i / sum(freq))

    return selectedNodes, nodesFreq, generatedset, matr


def optimization(matr):
    for i in range(len(matr)):
        rowSum = 0
        for j in range(len(matr[i]) - 1):
            rowSum += matr[i][j]
        matr[i][len(matr) - 1] = 1 - rowSum

    for j in range(len(matr[0])):
        colSum = 0
        for i in range(len(matr) - 1):
            colSum += matr[i][j]
        matr[len(matr[0]) - 1][j] = 1 - colSum

    return matr


def print_matrix(matrix):
    print('\nМатрица:')
    for i in range(n):
        for j in range(n):
            print("%7.3f" % (matrix[i][j]), end='    ')
        print()
    print()


def generate_two_stochastic_matrix():
    matrix1 = [[random.randint(0, 100) for i in range(n)] for j in range(n)]
    rowSum1 = [sum(e) for e in matrix1]

    matrix1 = normalization(matrix1, rowSum1)
    # print_matrix(matrix1)

    matrix2 = [[random.randint(0, 100) for i in range(n)] for j in range(n)];
    rowSum2 = [sum(e) for e in matrix2]

    matrix2 = normalization(matrix2, rowSum2)
    # print_matrix(matrix2)

    matrix2_transparent = [[matrix2[j][i] for j in range(len(matrix2))] for i in range(len(matrix2[0]))]
    matrix2 = matrix2_transparent
    # print_matrix(matrix2)

    two_stochastic_matrix = [[0 for i in range(n)] for j in range(n)]
    for i in range(len(matrix1)):
        for j in range(len(matrix2[0])):
            for k in range(len(matrix2)):
                two_stochastic_matrix[i][j] += matrix1[i][k] * matrix2[k][j]
    two_stochastic_matrix = optimization(two_stochastic_matrix)

    return two_stochastic_matrix


def get_Markov_chain():

    matrix = generate_two_stochastic_matrix()
    print_matrix(matrix)
    check_matrix(matrix)
    return Chain(matrix)


if __name__ == "__main__":

    selectedNodes1, freq1, set1, multyRes1 = get_Markov_chain()

    print('Переходы: ', selectedNodes1[0:show_size])
    print('Частота выбора переходов: ', [round(i, 3) for i in freq1])
    print('Сгенерированные значения: ', end=' ')
    for i in range(show_size):
        print("%5.3f" % set1[i], end=' ')
    print()
    print()

    fig, ax1 = plt.subplots()

    plot_acf(np.array(set1[shift:shift + show_size]), ax=ax1, alpha=None)

    selectedNodes2, freq2, set2, multyRes2 = get_Markov_chain()

    print('Переходы: ', selectedNodes1[0:show_size])
    print('Частота выбора переходов: ', [round(i, 3) for i in freq1])
    print('Сгенерированные значения: ', end=' ')
    for i in range(show_size):
        print("%5.3f" % set2[i], end=' ')
    print()
    print()

    plot_acf(np.array(set2[shift:shift + show_size]), ax=ax1, alpha=None, color='mediumseagreen', vlines_kwargs={"colors": 'mediumseagreen'})
    plt.grid()
    plt.show()

    print()
    plt.plot(range(show_size), set1[shift:shift + show_size])
    plt.plot(range(show_size), set2[shift:shift + show_size])
    plt.grid()
    plt.show()
