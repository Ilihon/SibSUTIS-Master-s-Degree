import sys

file_in, file_out = ("lepus.in"), "lepus.out"
sys.stdin = open(file_in, "r")
sys.stdout = open(file_out, "w")

n = int(input())
cells = input()

dp = [0] * n

for i in range(0, n):
    if cells[i] == 'w':
        dp[i] = -1000
    elif cells[i] == '"':
        dp[i] = 1

for i in range(0, n):
    if cells[i] != 'w':
        if i-5 >= 0:
            dp[i] += max(dp[i-1], dp[i-3], dp[i-5])
        elif i-3 >= 0:
            dp[i] += max(dp[i-1], dp[i-3])
        elif i-1 >= 0:
            dp[i] += dp[i-1]


print(-1 if dp[n - 1] < 0 else dp[n-1])
