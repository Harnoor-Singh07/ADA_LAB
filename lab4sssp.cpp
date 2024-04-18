#include <iostream>
#include <climits>
using namespace std;
void ShortestPaths(int v, int** cost, double* dist, int n) {
    bool* S = new bool[n];
    
    // Initialize distances and S set
    for (int i = 0; i < n; ++i) {
        S[i] = false;
        dist[i] = cost[v][i];
    }
    S[v] = true;
    dist[v] = 0.0;

    // Iterate over vertices
    for (int num = 2; num < n; ++num) {
        int u = -1;
        double minDist = INT_MAX;
        // Choose the vertex with minimum distance not in S
        for (int i = 0; i < n; ++i) {
            if (!S[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        // Put u in S
        S[u] = true;

        // Update distances
        for (int w = 0; w < n; ++w) {
            if (!S[w] && dist[w] > dist[u] + cost[u][w]) {
                dist[w] = dist[u] + cost[u][w];
            }
        }
    }

    delete[] S;
}

int main() {
    int n = 5; // Number of vertices
    int v = 0; // Source vertex

    // cost adjacency matrix
    int** cost = new int*[n];
    for (int i = 0; i < n; ++i) {
        cost[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            if (i == j)
                cost[i][j] = 0;
            else
                cost[i][j] = INT_MAX; // Initialize to maximum value
        }
    }
    cost[0][1] = 10;
    cost[0][3] = 5;
    cost[1][2] = 1;
    cost[1][3] = 2;
    cost[2][4] = 4;
    cost[3][1] = 3;
    cost[3][2] = 9;
    cost[3][4] = 2;

    double* dist = new double[n];

    // Call the ShortestPaths function
    ShortestPaths(v, cost, dist, n);

    // Output shortest distances
    cout << "Shortest distances from vertex " << v << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i << ": " << dist[i] << endl;
    }

    // Free memory
    for (int i = 0; i < n; ++i) {
        delete[] cost[i];
    }
    delete[] cost;
    delete[] dist;

    return 0;
}
