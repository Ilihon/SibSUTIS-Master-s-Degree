import random
import copy
from statistics import variance, pvariance, mean
from operator import itemgetter
import numpy as np
import matplotlib.pyplot as plt

n = 10
size = 20
max_interval = 4
max_service_time = 3


def generate_queue():
    matrix = []
    # interval = [round(random.uniform(0, max_interval), 7) for i in range(size)]
    # service_time = [round(random.uniform(0, max_service_time), 7) for i in range(size)]
    for i in range(size):
        interval = round(random.uniform(0, max_interval), 7)
        service_time = round(random.uniform(0, max_service_time), 7)
        line = {'interval': interval, 'service_time': service_time, 'add_moment': 0, 'await_time': 0}
        # print(line)
        matrix.append(line)
    # print()
    # print(matrix)
    return matrix


def set_all_values(matrix, key, value):
    for i in range(len(matrix)):
        matrix[i][key] = value


def calculate_awaits(matrix):
    i = 1
    matrix[0]['add_moment'] = 0
    matrix[0]['await_time'] = 0
    while i < len(matrix):
        matrix[i]['add_moment'] = round(matrix[i-1]['add_moment'] + matrix[i]['interval'], 7)
        matrix[i]['await_time'] = max(0, round(matrix[i-1]['await_time'] + matrix[i-1]['service_time'] - matrix[i]['interval'], 7))
        # print(matrix[i])
        i += 1
    # print()


def print_matrix(matrix):
    print("\t\t t  \t\t\t τ \t\t\t\t S \t\t\t\t W")
    for i in range(len(matrix)):
        print("\t%7.7f" % (matrix[i]['add_moment']), end='    ')
        print("\t%7.7f" % (matrix[i]['interval']), end='    ')
        print("\t%7.7f" % (matrix[i]['service_time']), end='    ')
        print("\t%7.7f" % (matrix[i]['await_time']), end='    ')
        print()
    print()


def estimate_matrix(matrix):
    # среднее арифметическое интервала / мат ожидание
    interval_middle = mean(matrix[i]['interval'] for i in range(len(matrix)))
    # среднее арифметическое времени обслуживания / мат ожидание
    service_time_middle = mean(matrix[i]['service_time'] for i in range(len(matrix)))
    # отношение
    Po = interval_middle/service_time_middle
    # среднее арифметическое времени ожидания
    await_time_middle = mean(matrix[i]['await_time'] for i in range(len(matrix)))
    # дисперсия генеральной совокупности
    dispersion = pvariance([matrix[i]['await_time'] for i in range(len(matrix))])

    print(f"E(τ):       {interval_middle}")
    print(f"E(S):       {service_time_middle}")
    print(f"Po:         {Po}")
    print(f"Среднее W:  {await_time_middle}")
    print(f"Дисперсия:  {dispersion}")
    print()


if __name__ == "__main__":
    w_unsorted = []
    w_sorted_asc = []
    w_sorted_desc = []
    width = 0.25

    print('Неотсортированное время обслуживания')
    matrix = generate_queue()
    calculate_awaits(matrix)
    print_matrix(matrix)
    estimate_matrix(matrix)
    w_unsorted = [matrix[i]['await_time'] for i in range(len(matrix))]

    print('Отсортированное по возврастанию время обслуживания')
    matrix_sorted = copy.deepcopy(matrix)
    matrix_sorted.sort(key=itemgetter('service_time'))
    calculate_awaits(matrix_sorted)
    print_matrix(matrix_sorted)
    estimate_matrix(matrix_sorted)
    w_sorted_asc = [matrix_sorted[i]['await_time'] for i in range(len(matrix_sorted))]

    print('Отсортированное по убыванию время обслуживания')
    matrix_sorted = copy.deepcopy(matrix)
    matrix_sorted.sort(key=itemgetter('service_time'), reverse=True)
    calculate_awaits(matrix_sorted)
    print_matrix(matrix_sorted)
    estimate_matrix(matrix_sorted)
    w_sorted_desc = [matrix_sorted[i]['await_time'] for i in range(len(matrix_sorted))]

    # print(w_unsorted)
    # print(w_sorted_asc)
    # print(w_sorted_desc)
    fig, axs = plt.subplots()
    axs.bar(np.arange(len(w_unsorted)), w_unsorted, width, label='W вразброс')
    axs.bar(np.arange(len(w_sorted_asc))+width, w_sorted_asc, width, label='W asc')
    axs.bar(np.arange(len(w_sorted_desc))+width*2, w_sorted_desc, width, label='W desc')
    plt.title('Случайные параметры')
    plt.grid()
    plt.legend()
    plt.show()

    print('Неотсортированное время обслуживания, при одинаковых интервалах')
    matrix_same_intervals = copy.deepcopy(matrix)
    set_all_values(matrix_same_intervals, 'interval', 1.2)
    calculate_awaits(matrix_same_intervals)
    print_matrix(matrix_same_intervals)
    estimate_matrix(matrix_same_intervals)
    w_unsorted = [matrix_same_intervals[i]['await_time'] for i in range(len(matrix_same_intervals))]

    print('Отсортированное по возрастанию время обслуживания, при одинаковых интервалах')
    matrix_sorted = matrix_same_intervals
    matrix_sorted.sort(key=itemgetter('service_time'))
    calculate_awaits(matrix_sorted)
    print_matrix(matrix_sorted)
    estimate_matrix(matrix_sorted)
    w_sorted_asc = [matrix_sorted[i]['await_time'] for i in range(len(matrix_sorted))]

    print('Отсортированное по убыванию время обслуживания, при одинаковых интервалах')
    matrix_sorted.sort(key=itemgetter('service_time'), reverse=True)
    calculate_awaits(matrix_sorted)
    print_matrix(matrix_sorted)
    estimate_matrix(matrix_sorted)
    w_sorted_desc = [matrix_sorted[i]['await_time'] for i in range(len(matrix_sorted))]

    fig, axs = plt.subplots()
    axs.bar(np.arange(len(w_unsorted)), w_unsorted, width, label='W вразброс')
    axs.bar(np.arange(len(w_sorted_asc))+width, w_sorted_asc, width, label='W asc')
    axs.bar(np.arange(len(w_sorted_desc))+width*2, w_sorted_desc, width, label='W desc')
    plt.title('С фиксированным интервалом')
    plt.grid()
    plt.legend()
    plt.show()

    print('Неотсортированные интервалы, при одинаковом времени обслуживания')
    matrix_same_service_time = copy.deepcopy(matrix)
    set_all_values(matrix_same_service_time, 'service_time', 2)
    calculate_awaits(matrix_same_service_time)
    print_matrix(matrix_same_service_time)
    estimate_matrix(matrix_same_service_time)
    w_unsorted = [matrix_same_service_time[i]['await_time'] for i in range(len(matrix_same_service_time))]

    print('Отсортированные по возрастанию интервалы, при одинаковом времени обслуживания')
    matrix_sorted = matrix_same_service_time
    matrix_sorted.sort(key=itemgetter('interval'))
    calculate_awaits(matrix_sorted)
    print_matrix(matrix_sorted)
    estimate_matrix(matrix_sorted)
    w_sorted_asc = [matrix_sorted[i]['await_time'] for i in range(len(matrix_sorted))]

    print('Отсортированные по убыванию интервалы, при одинаковом времени обслуживания')
    matrix_sorted.sort(key=itemgetter('interval'), reverse=True)
    calculate_awaits(matrix_sorted)
    print_matrix(matrix_sorted)
    estimate_matrix(matrix_sorted)
    w_sorted_desc = [matrix_sorted[i]['await_time'] for i in range(len(matrix_sorted))]

    fig, axs = plt.subplots()
    axs.bar(np.arange(len(w_unsorted)), w_unsorted, width, label='W вразброс')
    axs.bar(np.arange(len(w_sorted_asc))+width, w_sorted_asc, width, label='W asc')
    axs.bar(np.arange(len(w_sorted_desc))+width*2, w_sorted_desc, width, label='W desc')
    plt.title('С фиксированным временем обслуживания')
    plt.grid()
    plt.legend()
    plt.show()
