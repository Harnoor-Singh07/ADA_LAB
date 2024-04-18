#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
void perge(set<pair<int,int>>& s1) 
{
    auto it1 = s1.begin();
    
    while (it1 != s1.end()) {
        auto it2 = next(it1);

        if (it2 != s1.end() && it1->first <= it2->first && it1->second >= it2->second) {
            it1 = s1.erase(it1);
        } else {
            ++it1;
        }
    }
}
int knapsack(int W, vector<int>& wt, vector<int>& val, int n) {
    set<pair<int, int>> S;
    // Initialize the set with the base case
    S.insert({0, 0});
    for (int i = 0; i < n; i++) {
        // Create a temporary set to store intermediate results
        set<pair<int, int>> temp;
        for (auto it = S.begin(); it != S.end(); ++it) {
            int weight = it->first;
            int value = it->second;
            // Include the current item
            if (weight + wt[i] <= W) {
                temp.insert({weight + wt[i], value + val[i]});
            }
            // Discard the current item
            temp.insert(*it);
        }
        S = temp;
    }
    cout << "Before perge:" << endl;
    for (auto it = S.begin(); it != S.end(); ++it) {
        cout << "Weight: " << it->first << ", Value: " << it->second << endl;
    }
    perge(S);
    cout << "Optimal subproblems:" << endl;
    for (auto it = S.begin(); it != S.end(); ++it) {
        cout << " Value: " << it->second << ", Weight: " << it->first << endl;
    }

    // max
    return S.rbegin()->second;

}

int main() {
    int n; 
    cout << "Enter the number of items: ";
    cin >> n;
    vector<int> val(n);//profits of the the s
    vector<int> wt(n);  
    cout << "Enter the Profits of items: ";
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    cout << "Enter the weights of items: ";
    for (int i = 0; i < n; i++) {
        cin >> wt[i];
    }
    int W;
    cout << "Enter the maximum weight capacity of the knapsack: ";
    cin >> W;
    int maxVal = knapsack(W, wt, val, n);

    cout << "The maximum value that can be obtained is: " << maxVal << endl;

    return 0;
}

