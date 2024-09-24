import matplotlib.pyplot as plt
import numpy as np

x_to_y_1_func = lambda x: x                   # y = x
x_to_y_2_func = lambda x: np.power(x - 2, 2)  # y = (x - 2) ^ 2
y_to_x_1_func = lambda y: np.sqrt(y)          # x = square_root(y)
y_to_x_2_func = lambda y: np.cbrt(y - 1) + 2  # x = cube_root(y - 1) + 2
dots_count = 1000
probability = 0.6


def main_x():
    def calc_fig(x):
        bottom_y = x_to_y_1_func(x)
        top_y = x_to_y_2_func(x)
        if x <= 1:
            return np.random.uniform(0, bottom_y)
        else:
            return np.random.uniform(0, top_y)

    x_list = np.linspace(0, 2, dots_count)
    y_list_1 = list(map(x_to_y_1_func, x_list))
    y_list_2 = list(map(x_to_y_2_func, x_list))
    x_list_fig = np.concatenate((np.linspace(0, 1, int(dots_count * probability)), np.linspace(1, 2, int(dots_count * (1 - probability)))))  # 600 for 0.6 and 400 for 0.4
    y_list_fig = list(map(calc_fig, x_list_fig))

    fig, ax = plt.subplots()
    ax.grid()
    ax.scatter(x_list_fig, y_list_fig, color='lightblue', s=1)
    ax.plot(x_list, y_list_1, color='black')
    ax.plot(x_list, y_list_2, color='black')

    fig.savefig('plot_x.pdf')


def main_y():
    def calc_fig(y):
        left_x = y_to_x_1_func(y)
        right_x = y_to_x_2_func(y)
        r = np.random.uniform(0, 1)
        if r < probability:
            return np.random.uniform(left_x, 1)
        else:
            return np.random.uniform(1, right_x)

    y_list = np.linspace(0, 1, dots_count)
    x_list_1 = list(map(y_to_x_1_func, y_list))
    x_list_2 = list(map(y_to_x_2_func, y_list))
    y_list_fig = np.linspace(0, 1, dots_count)
    x_list_fig = list(map(calc_fig, y_list_fig))

    fig, ax = plt.subplots()
    ax.grid()
    ax.scatter(x_list_fig, y_list, color='lightblue', s=1)
    ax.plot(x_list_1, y_list, color='black')
    ax.plot(x_list_2, y_list, color='black')

    fig.savefig('plot_y.pdf')


if __name__ == '__main__':
    main_x()
    main_y()
