
import sys

from lab1 import *

if __name__ == '__main__':
    qubit = generate_qubit()
    a0 = qubit[0]
    a1 = qubit[1]
    print(f'[a0, a1]: {qubit}')

    hadamard = hadamard_matrix()
    b_matrix = np.dot(qubit, hadamard)
    b_matrix = b_matrix * (1 / sqrt(2))
    b0 = b_matrix[0]
    b1 = b_matrix[1]
    print(f'[b0, b1]: {b_matrix}')

    coef_pack = np.concatenate((qubit, b_matrix))

    # Алиса генерирует кубит находящийся с равными вероятностями в одном из четырех состояний:
    # 0, 1, 0', 1'
    Alice_basis = random.randint(0, 3)
    print(f'Alice basis: {Alice_basis}, {coef_pack[Alice_basis]}')
    Alice_detector = Alice_basis % 2
    print(f'Alice detector: {Alice_detector}')
    # meter = random.randint(0, 1)
    # coef_pack = np.concatenate((qubit, b_matrix))
    # print(coef_pack)
    # Alice_quibit = np.random.choice(coef_pack)
    # print(Alice_quibit)

    # Боб выбирает один из двух измерителей и сообщает Алисе
    Bob_detector = random.randint(0, 1)
    print(f'Bob detector: {Bob_detector}')
    if Bob_detector == Alice_detector:
        print('OK')
    else:
        print('Again')
        sys.exit()

    if Bob_detector == 0:
        Bob_quibit = qubit
    else:
        Bob_quibit = b_matrix

    print(Bob_quibit)
    result = qubit_solve(Bob_quibit[0])
    print(f'{result}')
