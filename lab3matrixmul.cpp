#include <iostream>
#include <vector>

#include <chrono>
using namespace std;
using namespace chrono;

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Function to subtract two matrices
vector<vector<int>> subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Strassen's algorithm for matrix multiplication
vector<vector<int>> strassenMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int newSize = n / 2;

        // Creating submatrices
        vector<vector<int>> A11(newSize, vector<int>(newSize));
        vector<vector<int>> A12(newSize, vector<int>(newSize));
        vector<vector<int>> A21(newSize, vector<int>(newSize));
        vector<vector<int>> A22(newSize, vector<int>(newSize));
        vector<vector<int>> B11(newSize, vector<int>(newSize));
        vector<vector<int>> B12(newSize, vector<int>(newSize));
        vector<vector<int>> B21(newSize, vector<int>(newSize));
        vector<vector<int>> B22(newSize, vector<int>(newSize));

        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

        // Recursive steps
        vector<vector<int>> P1 = strassenMultiply(A11, subtractMatrices(B12, B22));
        vector<vector<int>> P2 = strassenMultiply(addMatrices(A11, A12), B22);
        vector<vector<int>> P3 = strassenMultiply(addMatrices(A21, A22), B11);
        vector<vector<int>> P4 = strassenMultiply(A22, subtractMatrices(B21, B11));
        vector<vector<int>> P5 = strassenMultiply(addMatrices(A11, A22), addMatrices(B11, B22));
        vector<vector<int>> P6 = strassenMultiply(subtractMatrices(A12, A22), addMatrices(B21, B22));
        vector<vector<int>> P7 = strassenMultiply(subtractMatrices(A11, A21), addMatrices(B11, B12));

        // Calculating result submatrices
        vector<vector<int>> C11 = addMatrices(subtractMatrices(addMatrices(P5, P4), P2), P6);
        vector<vector<int>> C12 = addMatrices(P1, P2);
        vector<vector<int>> C21 = addMatrices(P3, P4);
        vector<vector<int>> C22 = subtractMatrices(subtractMatrices(addMatrices(P5, P1), P3), P7);

        // Combining result submatrices
        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }
    }

    return C;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void createGraph(int n) {
    vector<vector<int>> A(n, vector<int>(n, 1)); // Initialize matrix A with all elements as 1
    vector<vector<int>> B(n, vector<int>(n, 1)); // Initialize matrix B with all elements as 1

    auto start = high_resolution_clock::now();
    vector<vector<int>> C = strassenMultiply(A, B);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Size of matrices: " << n << "x" << n << endl;
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
}

int main() {
    // Specify the sizes of matrices for which execution time will be measured
    vector<int> sizes = {3, 5, 7, 9, 11, 13, 15};

    // Measure execution time for each matrix size
    for (int size : sizes) {
        createGraph(size);
    }

    return 0;
}
