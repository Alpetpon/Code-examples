#include <vector>

extern "C" __attribute__((visibility("default"))) void solveLinearEquations(double* matrixData, double* rightHandSide, int matrixOrder, double* solution) {
    std::vector<std::vector<double> > A(matrixOrder, std::vector<double>(matrixOrder));
    std::vector<double> b(matrixOrder);
    for (int i = 0; i < matrixOrder; ++i) {
        for (int j = 0; j < matrixOrder; ++j) {
            A[i][j] = matrixData[i * matrixOrder + j];
        }
        b[i] = rightHandSide[i];
    }

    for (int i = 0; i < matrixOrder; ++i) {
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < matrixOrder; ++k) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }

        if (maxRow != i) {
            for (int k = i; k < matrixOrder; ++k) {
                double tmp = A[i][k];
                A[i][k] = A[maxRow][k];
                A[maxRow][k] = tmp;
            }
            double tmp = b[i];
            b[i] = b[maxRow];
            b[maxRow] = tmp;
        }

        for (int k = i + 1; k < matrixOrder; ++k) {
            double coeff = -A[k][i] / A[i][i];
            for (int j = i; j < matrixOrder; ++j) {
                if (i == j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += coeff * A[i][j];
                }
            }
            b[k] += coeff * b[i];
        }
    }


    for (int i = matrixOrder - 1; i >= 0; --i) {
        solution[i] = b[i];
        for (int j = i + 1; j < matrixOrder; ++j) {
            solution[i] -= A[i][j] * solution[j];
        }
        solution[i] /= A[i][i];
    }
}
