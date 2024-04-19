#include <iostream>
#include <cstdlib>
using namespace std;

int x[100]; // Global array to store the positions of queens

//queen can be placed in the kth row and ith column
bool Place(int k, int i, int n) {
    for (int j = 1; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
            return false; // Two queens in the same column or in the same diagonal
        }
    }
    return true;
}

// using backtracking
void NQueens(int k, int n) {
    for (int i = 1; i <= n; i++) {
        if (Place(k, i, n)) {
            x[k] = i;
            if (k == n) {
                for (int j = 1; j <= n; j++) {
                    cout << x[j] << " ";
                }
                cout << endl;
            } else {
                NQueens(k + 1, n);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of queens (n): ";
    cin >> n;
    NQueens(1, n);
    return 0;
}
