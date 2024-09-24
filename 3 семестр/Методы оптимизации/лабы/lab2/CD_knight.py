import sys

file_in, file_out = "knight.in", "knight.out"
sys.stdin = open(file_in, "r")
sys.stdout = open(file_out, "w")


n, m = map(int, input().split())

dp = [[0] * m for _ in range(n)]
dp[0][0] = 1

for i in range(n):
    for j in range(m):
        if i >= 1 and j >= 2:
            dp[i][j] += dp[i - 1][j - 2]
        if i >= 2 and j >= 1:
            dp[i][j] += dp[i - 2][j - 1]


print(dp[n - 1][m - 1])
