import sys
import math

# Функция для вычисления нормы матрицы
def norm2(a, n):
    sum = 0.0
    for i in range(n):
        for j in range(n):
            sum += a[i][j] ** 2
    return math.sqrt(abs(sum))

# Функция для умножения матриц
def multiply_matrices(a, b, n):
    result = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                result[i][j] += a[i][k] * b[k][j]
    return result

# Функция для вычитания матриц
def subtract_matrices(a, b, n):
    result = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            result[i][j] = a[i][j] - b[i][j]
    return result

# Функция для нахождения обратной матрицы методом квадратного корня
def find_inverse_matrix(arr, n):
    s = [[0 for _ in range(n)] for _ in range(n)]
    str_matrix = [[0 for _ in range(n)] for _ in range(n)]
    e = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        e[i][i] = 1

    # Вычисление матрицы S и транспонированной матрицы S (str_matrix)
    for i in range(n):
        m = 0
        for k in range(i):
            m += s[k][i] ** 2
        if arr[i][i] - m < 0:
            print("Не выполняется одно из условий выполнения метода - один главный минор меньше нуля")
            sys.exit()

        s[i][i] = math.sqrt(arr[i][i] - m)
        str_matrix[i][i] = s[i][i]

        for j in range(i + 1, n):
            p = 0
            for k in range(i):
                p += s[k][i] * s[k][j]
            s[i][j] = (arr[i][j] - p) / s[i][i]
            str_matrix[j][i] = s[i][j]

    # Вычисление обратной матрицы
    inv_matrix = [[0 for _ in range(n)] for _ in range(n)]
    for j in range(n):
        y = [0 for _ in range(n)]
        x = [0 for _ in range(n)]
        for i in range(n):
            su = 0
            for k in range(i):
                su += str_matrix[i][k] * y[k]
            y[i] = (e[i][j] - su) / (str_matrix[i][i])
        for i in range(n - 1, -1, -1):
            su = 0
            for k in range(i, n):
                su += s[i][k] * x[k]
            x[i] = (y[i] - su) / s[i][i]
        for i in range(n):
            inv_matrix[i][j] = x[i]

    return inv_matrix

# Функция для итерационного уточнения обратной матрицы
def iterate_refinement(arr, n, epsilon):
    current_inv_matrix = find_inverse_matrix(arr, n)
    iteration = 0

    while True:
        next_inv_matrix = multiply_matrices(current_inv_matrix, subtract_matrices([[2 * arr[i][j] for j in range(n)] for i in range(n)], multiply_matrices(arr, current_inv_matrix, n), n), n)

        if norm2(subtract_matrices(next_inv_matrix, current_inv_matrix, n), n) < epsilon:
            return next_inv_matrix, iteration

        current_inv_matrix = next_inv_matrix
        iteration += 1

# Чтение матрицы из файла
with open('input.txt') as f:
    inp = f.readlines()
    inp = [line.rstrip() for line in inp]
    n = int(inp[0])
    arr = [[0 for _ in range(n)] for _ in range(n)]

    for i in range(n):
        q = inp[i + 1].split()
        for j in range(n):
            arr[i][j] = float(q[j])

# Выполнение итерационного уточнения
epsilon = 1e-6
result_matrix, iterations = iterate_refinement(arr, n, epsilon)

# Вывод результата и номера итерации
print("Результат:")
for row in result_matrix:
    print(row)
print("Количество итераций:", iterations)







