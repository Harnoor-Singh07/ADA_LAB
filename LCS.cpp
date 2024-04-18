#include <iostream>
#include <vector>
#include <string>

using namespace std;

pair<vector<vector<int>>, vector<vector<string>>> LCS_Length(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();

    // tables for lengths and directions
    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));
    vector<vector<string>> b(m + 1, vector<string>(n + 1, ""));

    // fill in the tables
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = "2"; // ↖
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = "1"; // ↑
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = "0"; // ←
            }
        }
    }

    return {c, b};
}

void Print_LCS(const vector<vector<string>>& b, const string& X, int i, int j) {
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == "2") {
        Print_LCS(b, X, i - 1, j - 1);
        cout << X[i - 1];
    } else if (b[i][j] == "1") {
        Print_LCS(b, X, i - 1, j);
    } else {
        Print_LCS(b, X, i, j - 1);
    }
}

int main() {
    string X, Y;
    cout << "Enter the first string: ";
    cin >> X;
    cout << "Enter the second string: ";
    cin >> Y;

    auto result = LCS_Length(X, Y);
    vector<vector<int>> c = result.first;
    vector<vector<string>> b = result.second;

    cout << "Length of the Longest Common Subsequence: " << c[X.length()][Y.length()] << endl;

    cout << "Longest Common Subsequence: ";
    Print_LCS(b, X, X.length(), Y.length());
    cout << endl;

    return 0;
}
