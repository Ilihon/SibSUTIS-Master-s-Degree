import random


def generate_random_propability(N: int):
    propabilities = []
    sum = 0
    check_sum = 0

    for i in range(N):
        propabilities.append(random.randint(1, 100))
        sum = sum + propabilities[i]

    for i in range(N):
        check_sum = check_sum + round(propabilities[i] / sum, 4)
        propabilities[i] = round(propabilities[i] / sum, 4)

    if check_sum != 1.:
        propabilities[-1] = round(propabilities[-1] + 1. - check_sum, 4)

    return propabilities


def select_without_repeats(propabilities_list: list, selection_size):
    index_counters = []
    index_mass = []
    for i in propabilities_list:
        index_counters.append(int(i * 10000))
    # print(index_counters)

    for i in range(len(index_counters)):
        for j in range(index_counters[i]):
            index_mass.append(i)
    # print(index_mass)

    random.shuffle(index_mass)
    selection = []
    for i in range(selection_size):
        selection.append(index_mass[0])
        new_index_mass = []
        for j in range(len(index_mass)):
            if index_mass[j] != selection[-1]:
                new_index_mass.append(index_mass[j])
        index_mass = new_index_mass

    return selection


if __name__ == "__main__":
    propabilities = generate_random_propability(10)
    # propabilities = [0.1863, 0.0288, 0.1153, 0.1641, 0.2195, 0.082, 0.02, 0.0665, 0.071, 0.0465]
    print("Вероятности:", propabilities)
    runs_count = 100
    rating = []
    for i in range(len(propabilities)):
        rating.append(0)

    print("Выборки:")
    for i in range(runs_count):
        selection = select_without_repeats(propabilities, 5)
        for j in range(len(selection)):
            rating[selection[j]] = rating[selection[j]] + (len(propabilities) - j)
        print(selection)

    print("\nБаллы:", rating)
