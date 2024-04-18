#include<iostream>
#include<vector>
#include<algorithm>
#include <chrono>
using namespace std;
using namespace chrono;
#include<cstdlib>



int find(int i, vector<int>& p) {
    while (p[i] > 0) {
        i = p[i];
    }
    return i;
}

void UnionSets(int i, int j, vector<int>& p) {
    p[i] = j;
}

void heapify(vector<pair<int, int>>& edges, int N, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < N && edges[l] < edges[smallest])
        smallest = l;
 
    if (r < N && edges[r] < edges[smallest])
        smallest = r;
 
    if (smallest != i) {
        swap(edges[i], edges[smallest]);
        heapify(edges, N, smallest);
    }
}

void buildHeap(vector<pair<int, int>>& edges) {
    int N = edges.size();
    int startIdx = (N / 2) - 1;
    for (int i = startIdx; i >= 0; i--) {
        heapify(edges, N, i);
    }
}

void kruskal(vector<pair<int, int>>& edges, vector<vector<int>>& cost, int n, vector<pair<int, int>>& t) {
    buildHeap(edges);
    vector<int> parent(n, -1);
    int mincost = 0;
    int i = 0;
    
    while (i < n && !edges.empty()) {
        pair<int, int> minEdge = edges.front();
        swap(edges[0], edges[edges.size() - 1]);
        edges.pop_back();
        heapify(edges, edges.size(), 0);

        int u = minEdge.first;
        int v = minEdge.second;

        int j = find(u, parent);
        int k = find(v, parent);

        if (j != k) {
            t.push_back(minEdge);
            mincost += cost[u][v];
            i++;
            UnionSets(j, k, parent);
        }
    }

    cout << "Minimum Cost of Spanning Tree: " << mincost << endl;
}

void createGraph(int numVertices) {
    vector<pair<int, int>> t; // Minimum spanning tree edges

    // Populate cost matrix with random values
    vector<vector<int>> cost(numVertices, vector<int>(numVertices, 0));
    vector<pair<int, int>> edges;
    for (int j = 0; j < numVertices; j++) {
        for (int k = j + 1; k < numVertices; k++) {
            cost[j][k] = rand() % 101; // Values range from 0 to 100
            cost[k][j] = cost[j][k]; // Undirected graph
            edges.push_back(make_pair(j, k));
        }
    }

    // Measure execution time
    auto start = high_resolution_clock::now();
    kruskal(edges, cost, numVertices, t);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Number of vertices: " << numVertices << ", Execution time: " << duration.count() << " milliseconds" << endl;
}

int main() {
    for (int i = 10; i <= 100; i += 10) {
        createGraph(i);
    }
    return 0;
}
