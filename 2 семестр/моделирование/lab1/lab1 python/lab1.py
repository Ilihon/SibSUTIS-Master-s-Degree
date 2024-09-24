import matplotlib.pyplot as plt
import math
import random
import numpy as np


def var1():

    n = 500

    plt.grid()

    x_sin = np.linspace(0, math.pi / 2, 20)
    y_sin = np.sin(x_sin)
    plt.plot(x_sin, y_sin, color="red")

    x_cos = np.linspace(0, math.pi / 2, 20)
    y_cos = np.cos(x_cos)
    plt.plot(x_cos, y_cos, color="orange")

    x1 = []
    x2 = []
    f1 = []
    f2 = []

    # Функция y = sin(x)
    for i in range(n):

        rand = random.random()
        x1.append(math.acos(1 - rand + (rand * math.sqrt(2)) / 2))

        f1.append(math.sin(x1[i]) * random.uniform(0, 1))

    # Функция y = сos(x)
    for i in range(n):

        rand = random.random()
        x2.append(math.asin(rand / (2 + math.sqrt(2)) + (math.sqrt(2) / 2)))

        f2.append(math.cos(x2[i]) * random.uniform(0, 1))

    plt.plot(x1, f1, 'b+')

    plt.plot(x2, f2, 'r+')

    plt.xlim(0, 1.75)
    plt.ylim(0, 1.2)
    plt.text(0.1, 0.8, 'y = сos(x)')
    plt.text(1.1, 0.8, 'y = sin(x)')

    plt.show()


def var2():

    n = 50
    middle = np.pi / 4
    parts = 5

    plt.grid()

    x_sin = np.linspace(0, middle, 20)
    # x_sin = np.linspace(middle, np.pi / 2, 20)
    # x_sin = np.linspace(0, np.pi / 2, 20)
    y_sin = np.sin(x_sin)
    t_sin = np.polyfit(x_sin, y_sin, parts)
    f_sin = np.poly1d(t_sin)

    x_sin_full = np.linspace(0, np.pi / 2, 20)
    y_sin_full = np.sin(x_sin_full)
    print(f_sin)
    # roots_sin = np.roots(t_sin)
    # print(roots_sin)
    plt.plot(x_sin_full, y_sin_full,  label='y = sin(x)', color="green")
    plt.plot(x_sin, y_sin, x_sin, f_sin(x_sin),  label='y = sin(x) full', color="red")

    x_cos = np.linspace(middle, np.pi / 2, 20)
    # x_cos = np.linspace(0, middle, 20)
    # x_cos = np.linspace(0, np.pi / 2, 20)
    y_cos = np.cos(x_cos)
    t_cos = np.polyfit(x_cos, y_cos, parts)
    f_cos = np.poly1d(t_cos)

    x_cos_full = np.linspace(0, np.pi / 2, 20)
    y_cos_full = np.cos(x_cos_full)
    print('\n', f_cos)
    # roots_cos = np.roots(t_cos)
    # print(roots_cos)
    plt.plot(x_cos_full, y_cos_full,  label='y = cos(x)', color="magenta")
    plt.plot(x_cos, y_cos, x_cos, f_cos(x_cos),  label='y = cos(x) full', color="orange")

    x1 = []
    x2 = []
    f1 = []
    f2 = []

    # Функция y = sin x

    for i in range(n):
        buf = 0
        # rand = random.random()
        rand = random.uniform(0, middle)
        for j in range(parts):
            buf += f_sin.c[j] * random.uniform(0, middle)
        buf += f_sin.c[parts]
        # x1.append(buf)
        x1.append(rand)
        # f1.append(np.sin(buf))
        f1.append(np.sin(rand))

    plt.plot(x1, f1, 'b+')

    # Функция y = cos x

    for i in range(n):
        buf = 0
        # rand = random.random()
        rand = random.uniform(middle, np.pi/2)
        # rand = random.uniform(0, np.pi/2)
        # rand = random.uniform(0, middle)
        for j in range(parts):
            buf += f_sin.c[j] * random.uniform(middle, np.pi/2)
            # print(f_sin.c[j])
        buf += f_sin.c[parts]
        # x2.append(buf)
        x2.append(rand)
        # f2.append(np.cos(buf))
        f2.append(np.cos(rand))

    plt.plot(x2, f2, 'r+')

    plt.xlim(0, 1.75)
    plt.ylim(0, 1.2)
    plt.text(0.1, 0.8, 'y = сos(x)')
    plt.text(1.1, 0.8, 'y = sin(x)')

    plt.show()


var2()
