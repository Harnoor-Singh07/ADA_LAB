#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

void WriteDataToFile(int i, double avgTime) {
    ofstream fout("data.txt", ios::app);
    if (fout.is_open()) {
        fout << i << "," << avgTime << endl;
        fout.close();
    } else {
        cout << "Unable to open file for writing data." << endl;
    }
}

typedef vector<vector<int>> Matrix;

Matrix add_matrices(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix result(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

Matrix subtract_matrices(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix result(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

void split_matrix(const Matrix& A, Matrix& A11, Matrix& A12, Matrix& A21, Matrix& A22) {
    int n = A.size() / 2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n];
            A21[i][j] = A[i + n][j];
            A22[i][j] = A[i + n][j + n];
        }
    }
}

Matrix strassen_multiply(const Matrix& A, const Matrix& B) {
    int n = A.size();

    // Base case: When the matrix size is 1x1
    if (n == 1) {
        Matrix C(1, vector<int>(1, 0));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Split matrices into quadrants
    Matrix A11(n / 2, vector<int>(n / 2, 0));
    Matrix A12(n / 2, vector<int>(n / 2, 0));
    Matrix A21(n / 2, vector<int>(n / 2, 0));
    Matrix A22(n / 2, vector<int>(n / 2, 0));
    Matrix B11(n / 2, vector<int>(n / 2, 0));
    Matrix B12(n / 2, vector<int>(n / 2, 0));
    Matrix B21(n / 2, vector<int>(n / 2, 0));
    Matrix B22(n / 2, vector<int>(n / 2, 0));
    split_matrix(A, A11, A12, A21, A22);
    split_matrix(B, B11, B12, B21, B22);

    // Strassen's algorithm
    Matrix M1 = strassen_multiply(add_matrices(A11, A22), add_matrices(B11, B22));
    Matrix M2 = strassen_multiply(add_matrices(A21, A22), B11);
    Matrix M3 = strassen_multiply(A11, subtract_matrices(B12, B22));
    Matrix M4 = strassen_multiply(A22, subtract_matrices(B21, B11));
    Matrix M5 = strassen_multiply(add_matrices(A11, A12), B22);
    Matrix M6 = strassen_multiply(subtract_matrices(A21, A11), add_matrices(B11, B12));
    Matrix M7 = strassen_multiply(subtract_matrices(A12, A22), add_matrices(B21, B22));

    Matrix C11 = add_matrices(subtract_matrices(add_matrices(M1, M4), M5), M7);
    Matrix C12 = add_matrices(M3, M5);
    Matrix C21 = add_matrices(M2, M4);
    Matrix C22 = add_matrices(subtract_matrices(add_matrices(M1, M3), M2), M6);

    // Combine submatrices to get the result
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n / 2; ++i) {
        for (int j = 0; j < n / 2; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + n / 2] = C12[i][j];
            C[i + n / 2][j] = C21[i][j];
            C[i + n / 2][j + n / 2] = C22[i][j];
        }
    }
    return C;
}

void initialize_random_matrix(Matrix& c, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            c[i][j] = rand();
        }
    }
}

int main() {
    double avgtime, time1, time2;
    for (int i = 2; i < 200; i = 2 * i) {
        Matrix A(i, vector<int>(i, 0));
        Matrix B(i, vector<int>(i, 0));

        initialize_random_matrix(A, i);
        initialize_random_matrix(B, i);

        time1 = (double)clock();
        for (int j = 0; j < 10; j++) {
            Matrix result = strassen_multiply(A, B);
        }
        time2 = (double)clock();

        avgtime = (double)(time2 - time1) / 10;
        cout << i << " " << avgtime << endl;
        WriteDataToFile(i, avgtime * 500);
    }

    return 0;
}
