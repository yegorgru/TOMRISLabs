import random
import time
import os

ROW_1 = 4
COL_1 = 4
ROW_2 = 4
COL_2 = 4


# Function to print the matrix
def printMat(a, r, c):
    for i in range(r):
        for j in range(c):
            print(a[i][j], end=" ")
        print()
    print()


# Function to print the matrix
def printt(display, matrix, start_row, start_column, end_row, end_column):
    print(display + " =>\n")
    for i in range(start_row, end_row + 1):
        for j in range(start_column, end_column + 1):
            print(matrix[i][j], end=" ")
        print()
    print()


# Function to add two matrices
def add_matrix(matrix_A, matrix_B, matrix_C, split_index):
    for i in range(split_index):
        for j in range(split_index):
            matrix_C[i][j] = matrix_A[i][j] + matrix_B[i][j]

        # Function to initialize matrix with zeros


def initWithZeros(a, r, c):
    for i in range(r):
        for j in range(c):
            a[i][j] = 0

def get_randomized_matrix(size):
    # Generate 5 random numbers between 10 and 30
    res = list()
    for i in range(size):
        res.append(random.sample(range(1, 100), size))
    return res

# Function to multiply two matrices
def multiply_matrix(matrix_A, matrix_B):
    col_1 = len(matrix_A[0])
    row_1 = len(matrix_A)
    col_2 = len(matrix_B[0])
    row_2 = len(matrix_B)

    if (col_1 != row_2):
        print("\nError: The number of columns in Matrix A must be equal to the number of rows in Matrix B\n")
        return 0

    result_matrix_row = [0] * col_2
    result_matrix = [[0 for x in range(col_2)] for y in range(row_1)]

    if (col_1 == 1):
        result_matrix[0][0] = matrix_A[0][0] * matrix_B[0][0]

    else:
        split_index = col_1 // 2

        row_vector = [0] * split_index
        result_matrix_00 = [[0 for x in range(split_index)] for y in range(split_index)]
        result_matrix_01 = [[0 for x in range(split_index)] for y in range(split_index)]
        result_matrix_10 = [[0 for x in range(split_index)] for y in range(split_index)]
        result_matrix_11 = [[0 for x in range(split_index)] for y in range(split_index)]
        a00 = [[0 for x in range(split_index)] for y in range(split_index)]
        a01 = [[0 for x in range(split_index)] for y in range(split_index)]
        a10 = [[0 for x in range(split_index)] for y in range(split_index)]
        a11 = [[0 for x in range(split_index)] for y in range(split_index)]
        b00 = [[0 for x in range(split_index)] for y in range(split_index)]
        b01 = [[0 for x in range(split_index)] for y in range(split_index)]
        b10 = [[0 for x in range(split_index)] for y in range(split_index)]
        b11 = [[0 for x in range(split_index)] for y in range(split_index)]

        for i in range(split_index):
            for j in range(split_index):
                a00[i][j] = matrix_A[i][j]
                a01[i][j] = matrix_A[i][j + split_index]
                a10[i][j] = matrix_A[split_index + i][j]
                a11[i][j] = matrix_A[i + split_index][j + split_index]
                b00[i][j] = matrix_B[i][j]
                b01[i][j] = matrix_B[i][j + split_index]
                b10[i][j] = matrix_B[split_index + i][j]
                b11[i][j] = matrix_B[i + split_index][j + split_index]

        add_matrix(multiply_matrix(a00, b00), multiply_matrix(a01, b10), result_matrix_00, split_index)
        add_matrix(multiply_matrix(a00, b01), multiply_matrix(a01, b11), result_matrix_01, split_index)
        add_matrix(multiply_matrix(a10, b00), multiply_matrix(a11, b10), result_matrix_10, split_index)
        add_matrix(multiply_matrix(a10, b01), multiply_matrix(a11, b11), result_matrix_11, split_index)

        for i in range(split_index):
            for j in range(split_index):
                result_matrix[i][j] = result_matrix_00[i][j]
                result_matrix[i][j + split_index] = result_matrix_01[i][j]
                result_matrix[split_index + i][j] = result_matrix_10[i][j]
                result_matrix[i + split_index][j + split_index] = result_matrix_11[i][j]

    return result_matrix


# Driver Code
matrix_A = get_randomized_matrix(8)

print("Array A =>")
printMat(matrix_A, 8, 8)

matrix_B = get_randomized_matrix(8)

print("Array B =>")
printMat(matrix_B, 8, 8)

start_time = time.perf_counter()
result_matrix = multiply_matrix(matrix_A, matrix_B)
end_time = time.perf_counter()
elapsed_time = end_time - start_time

print("Result Array =>")
printMat(result_matrix, 8, 8)

print("Time: ", elapsed_time)
