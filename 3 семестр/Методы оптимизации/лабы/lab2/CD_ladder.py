import sys
#
# file_out = "ladder.out"
# sys.stdout = open(file_out, "w")

file_in, file_out = "ladder.in", "ladder.out"
sys.stdin = open(file_in, "r")
sys.stdout = open(file_out, "w")
n = int(input())
a = list(map(int, input().split()))


a = [0] + a

for i in range(2, n + 1):
    a[i] += max(a[i - 1], a[i - 2])

print(a[n])