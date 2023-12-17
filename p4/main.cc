#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sched.h>
#include <mpi.h>

using namespace std;

#define N 4 // Assuming square matrices of size NxN

void initializeMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10; // Fill matrix with random values for testing
        }
    }
}

void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void matrixMultiply(int a[N][N], int b[N][N], int result[N][N], int startRow, int endRow, int rank) {
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }

            char processorName[MPI_MAX_PROCESSOR_NAME];
            int nameLen;
            MPI_Get_processor_name(processorName, &nameLen);
            cout << "Process " << rank << " on machine " << processorName << " is computing result[" << i << "][" << j << "]" << endl;
        }
    }
}

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL));

    int matrixA[N][N];
    int matrixB[N][N];
    int result[N][N];

    int blockSize = N / size;

    if (rank == 0) {
        initializeMatrix(matrixA);
        initializeMatrix(matrixB);
        cout << "Matrix A:" << endl;
        printMatrix(matrixA);
        cout << "Matrix B:" << endl;
        printMatrix(matrixB);
    }

    MPI_Bcast(matrixA, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(matrixB, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    int startRow = rank * blockSize;
    int endRow = (rank + 1) * blockSize;

    matrixMultiply(matrixA, matrixB, result, startRow, endRow, rank);

    // Collect individual results from each process
    MPI_Gather(result + startRow, blockSize * N, MPI_INT, result, blockSize * N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Matrix multiplication result:" << endl;
        printMatrix(result);
    }

    MPI_Finalize();

    return 0;
}