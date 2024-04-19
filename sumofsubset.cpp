#include <iostream>
#include <vector>
using namespace std;
void writeSubset(const vector<int>& subset) {
    cout << "Subset: { ";
    for (int i = 0; i < subset.size(); ++i) {
        if (subset[i] == 1) {
            cout << i + 1 << " ";
        }
    }
    cout << "}" << endl;
}
void sumOfSub(vector<int>& x, const vector<int>& w, int s, int k, int r, int m) {
    // left child
    x[k] = 1;
    if (s + w[k] == m) {
        writeSubset(x);
    } else if (s + w[k] + w[k + 1] <= m) {
        sumOfSub(x, w, s + w[k], k + 1, r - w[k], m);
    }
    // right child and evaluate Bk
    if ((s + r - w[k] >= m) && (s + w[k + 1] <= m)) {
        x[k] = 0;
        sumOfSub(x, w, s, k + 1, r - w[k], m);
    }
}
void SumOfSub(const vector<int>& w, int m) {
    int n = w.size();
    vector<int> x(n, 0); // x[i] represents whether element i is included in the subset or not
    int s = 0; 
    int r = 0; // Sum of remaining elements
    for (int j = 0; j < n; ++j) {
        r += w[j];
    }
    sumOfSub(x, w, s, 0, r, m);
}
int main() {
    vector<int> weights = {1, 2, 3, 4, 5}; // Weights of elements
    int targetSum = 10; 
    SumOfSub(weights, targetSum);
    return 0;
}
