
if __name__ == "__main__":

    with open('lepus.in', 'r') as file:
        n = int(file.readline().strip())
        cells = file.readline().strip()

    dp = [-1] * n
    dp[0] = -2

    # print(dp)
    # print(cells)
    for i in range(0, n):
        if dp[i] != -1:
            # print()
            # print(i)
            for j in range(i+1, min(i + 5, n), 2):
                # print(j, dp[j], cells[j])
                if cells[j] == 'w':
                    dp[j] = -1
                    continue
                if cells[j] == '.':
                    dp[j] = 0
                if cells[j] == '"':
                    dp[j] = 1 if dp[i] <= -1 else dp[i] + 1

    max_grass = max(dp)
    print(f"input: \n{n}\n{cells}\n")
    print(f"output: \n{max_grass}")
