import sys

# file_in, file_out = "slalom.in", "slalom.out"
# sys.stdin = open(file_in, "r")
# sys.stdout = open(file_out, "w")

triangle = []

n = int(input())
for _ in range(n):
    row = list(map(int, input().split()))
    triangle.append(row)

n = len(triangle)

# Создаем таблицу для хранения сумм очков
dp = [[0] * n for _ in range(n)]

# Заполняем последнюю строку таблицы
for j in range(n):
    dp[n - 1][j] = triangle[n - 1][j]

# Заполняем остальную часть таблицы
for i in range(n - 2, -1, -1):
    for j in range(i + 1):
        dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + triangle[i][j]

print(dp[0][0])
