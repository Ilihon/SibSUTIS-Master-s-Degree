

if __name__ == "__main__":

    triangle = []

    with open('slalom.in', 'r') as file:
        n = int(file.readline())
        for _ in range(n):
            row = list(map(int, file.readline().split()))
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

    print(f"input:")
    for i in range(0, n):
        print(triangle[i])

    print(f"\noutput: \n{dp[0][0]}")

    # for i in range(0, n):
    #     print(dp[i])
