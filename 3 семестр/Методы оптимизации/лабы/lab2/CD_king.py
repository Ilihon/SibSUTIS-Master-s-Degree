import sys

file_in, file_out = "king2.in", "king2.out"
sys.stdin = open(file_in, "r")
sys.stdout = open(file_out, "w")

grid = []

for _ in range(8):
    row = list(map(int, input().split()))
    grid.append(row)

n = len(grid)
m = len(grid[0])

grid.reverse()

dp = [[0] * m for _ in range(n)]
dp[0][0] = grid[0][0]

# Инициализация первого столбца
for i in range(1, n):
    dp[i][0] = dp[i - 1][0] + grid[i][0]

# Инициализация первой строки
for j in range(1, m):
    dp[0][j] = dp[0][j - 1] + grid[0][j]

# Заполнение остальной части таблицы
for i in range(1, n):
    for j in range(1, m):
        dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + grid[i][j]

print(dp[n - 1][m - 1])
