#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
using namespace std;
using namespace chrono;

int Prim(vector<vector<int>>& cost, int n, vector<vector<int>>& t) {
    vector<int> near(n);
    int mincost = INT_MAX;

    // Find the edge of minimum cost
    int k, l;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (cost[i][j] < mincost) {
                mincost = cost[i][j];
                k = i;
                l = j;
            }
        }
    }

    t[0][0] = k;
    t[0][1] = l;

    // Initialize near[]
    for (int i = 0; i < n; ++i) {
        near[i] = (cost[i][l] < cost[i][k]) ? l : k;
    }
    near[k] = near[l] = 0;

    // Find additional edges for t
    for (int i = 1; i < n - 1; ++i) {
        int j;
        int min = INT_MAX;
        for (int index = 0; index < n; ++index) {
            if (near[index] != 0 && cost[index][near[index]] < min) {
                min = cost[index][near[index]];
                j = index;
            }
        }
        t[i][0] = j;
        t[i][1] = near[j];
        mincost += min;
        near[j] = 0;

        // Update near[]
        for (int k = 0; k < n; ++k) {
            if (near[k] != 0 && cost[k][near[k]] > cost[k][j]) {
                near[k] = j;
            }
        }
    }

    return mincost;
}

void createGraph() {
    int avgtime = 0;
    for (int i = 1000; i <= 100000; i += 1000) {
        vector<vector<int>> cost(i, vector<int>(i, 0));
        
        // Randomly generate cost adjacency matrix
        for (int j = 0; j < i; ++j) {
            for (int k = 0; k < i; ++k) {
                if (j != k)
                    cost[j][k] = rand() % 100; // Random cost between 0 and 99
            }
        }

        vector<vector<int>> t(i - 1, vector<int>(2));

        int total_time = 0;
        for (int j = 1; j <= 10; j++) {
            auto start1 = high_resolution_clock::now();
            int mincost = Prim(cost, i, t);
            auto stop1 = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop1 - start1);
            total_time += duration.count();
        }
        avgtime = total_time / 10;
        cout << "Avg time taken for array of " << i << " elements is " << avgtime << " microseconds" << endl;
    }
}

int main() {
    createGraph();

    return 0;
}
