import sys

if __name__ == "__main__":
    with open('ladder.in', 'r') as file:
        n = int(file.readline().strip())
        a = list(map(int, file.readline().split()))


    # file_in, file_out = "ladder.in", "ladder.out"
    # sys.stdin = open(file_in, "r")
    # sys.stdout = open(file_out, "w")
    # n = int(input())
    # a = list(map(int, input().split()))

    print(f"input: \n{n}\n{a}\n")

    if len(a) != n:
        print("Количество чисел a не соответствует значению n")
        exit()

    # /////////////////////////////////////////
    # первый вариант
    dp = [0] * (n + 1)
    dp[0] = 0
    dp[1] = a[0]

    for i in range(2, n + 1):
        # print(f" {dp[i-1]}; {dp[i-2]} + {a[i-1]}")
        dp[i] = max(dp[i-1], dp[i-2]) + a[i-1]
        # print(dp)

    print(dp)
    max_sum = dp[n]
    print(f"output: \n{max_sum}")

    # /////////////////////////////////////////
    # второй вариант
    a = [0] + a

    for i in range(2, n + 1):
        a[i] += max(a[i - 1], a[i - 2])

    max_sum = a[n]
    print(f"\n{a}")
    print(f"output: \n{max_sum}")

