

if __name__ == "__main__":

    grid = []

    with open('king.in', 'r') as file:
        for _ in range(8):
            row = list(map(int, file.readline().split()))
            grid.append(row)

    n = len(grid)
    m = len(grid[0])

    print(f"input:")
    for i in range(0, n):
        print(grid[i])

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

    print(f"\noutput: \n{dp[n - 1][m - 1]}")

    # for i in range(0, n):
    #     print(dp[i])
