import sys


# Значения # (хранятся в списке `v`)
# Вес # (хранится в списке `w`)
# Общее количество отдельных элементов `n`
# 1ТП4Т Рюкзак вместимостью `W`
def knapsack(v, w, n, W, lookup):
    # Базовый случай: отрицательная емкость
    if W < 0:
        return -sys.maxsize

    # Базовый случай: элементов не осталось или вместимость становится равной 0
    if n < 0 or W == 0:
        return 0

    # создает уникальный ключ из динамических элементов ввода
    key = (n, W)

    # , если подзадача видится впервые, решите ее и
    # сохраняет результат в словаре
    if key not in lookup:
        # Случай 1. Включить текущий предмет `v[n]` в рюкзак и повторять для
        # Осталось # элементов `n-1` с уменьшенной емкостью `W-w[n]`
        include = v[n] + knapsack(v, w, n - 1, W - w[n], lookup)

        # Случай 2. Исключить текущий элемент `v[n]` из рюкзака и повторить для
        # оставшиеся элементы `n-1`
        exclude = knapsack(v, w, n - 1, W, lookup)

        # назначает максимальное значение, которое мы получаем, включая или исключая текущий элемент
        lookup[key] = max(include, exclude)

    # возвращает решение текущей подзадачи
    return lookup[key]


def boundedknapsack(val, wt, n, W):

    K = [[0 for x in range(W + 1)] for x in range(n + 1)]
    print(K)
    # Build table K[][] in bottom up manner
    for i in range(n + 1):
        for w in range(W + 1):
            if i == 0 or w == 0:
                K[i][w] = 0
            elif wt[i - 1] <= w:
                # print(val[i-1], K[i - 1][w - wt[i - 1]], K[i-1][w])
                K[i][w] = max(val[i - 1]
                              + K[i - 1][w - wt[i - 1]],
                              K[i - 1][w])
            else:
                K[i][w] = K[i - 1][w]

    print(K)
    return K[n][W]


def unboundedKnapsack(W, n, w, v):
    dp = []

    for i in range(W + 1):
        dp.append(0)

    for i in range(0, W + 1):
        for j in range(0, n):
            if i - w[j] >= 0:
                dp[i] = max(dp[i], dp[i - w[j]] + v[j])

    return dp[W]


if __name__ == '__main__':

    with open('rukzak.txt') as f:
        items = [list(map(int, row.split())) for row in f.readlines()]

    W = items[0][0]
    items.pop(0)

    print("Вместимость рюкзака:", W)
    w = [item[0] for item in items]
    v = [item[1] for item in items]

    # создает словарь для хранения решений подзадач
    lookup = {}


    print('Стоимость ограниченного рюкзака:', knapsack(v, w, len(v) - 1, W, lookup))
    print('Стоимость ограниченного рюкзака:', boundedknapsack(v, w, len(v), W))
    print("Стоимость неограниченного рюкзака: ", unboundedKnapsack(W, len(v) - 1, w, v))

