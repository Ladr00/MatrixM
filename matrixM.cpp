#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int ROWS = 3;
const int COLS = 3;

void matrix(int matrix[][COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void visualmatrix(int matrix[][COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void matrixM(int matrixA[][COLS], int matrixB[][COLS], int result[][COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

int main() {
    srand(time(0));

    int matrixA[ROWS][COLS];
    int matrixB[ROWS][COLS];
    int result[ROWS][COLS];

    matrix(matrixA, ROWS, COLS);
    matrix(matrixB, ROWS, COLS);

    std::cout << "Matrix A:" << std::endl;
    visualmatrix(matrixA, ROWS, COLS);

    std::cout << std::endl;

    std::cout << "Matrix B:" << std::endl;
    visualmatrix(matrixB, ROWS, COLS);

    std::cout << std::endl;

    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Fork failed" << std::endl;
        return 1;
    }
    else if (pid == 0) {
        matrixM(matrixA, matrixB, result, ROWS, COLS);

        std::cout << "Result (Child Process):" << std::endl;
        visualmatrix(result, ROWS, COLS);
    }
    else {
        int status;
        waitpid(pid, &status, 0);

        std::cout << "Result (Parent Process):" << std::endl;
        visualmatrix(result, ROWS, COLS);
    }

    return 0;
}
