

if __name__ == "__main__":
    with open('knight2.in', 'r') as file:
        n, m = map(int, file.readline().split())

    if not (1 <= n <= 50 and 1 <= m <=50):
        print("Входные данные не входят диапазон чисел от 1 до 50")
        exit()


    dp = [[0] * m for _ in range(n)]
    dp[0][0] = 1

    for i in range(n):
        for j in range(m):
            if i >= 1 and j >= 2:
                dp[i][j] += dp[i - 1][j - 2]
            if i >= 2 and j >= 1:
                dp[i][j] += dp[i - 2][j - 1]


    print(f"input: \n{n}\n{m}\n")
    print(f"output: \n{dp[n - 1][m - 1]}")
