#include <iostream>
using namespace std;

const int INFINITY = 99999;
int colors[100];

void nextVal(int k, int n, int m, int graph[][100]) {
    int i;
    do {
        colors[k] = (colors[k] + 1) % (m + 1);
        if (colors[k] == 0) {
            return;
        }
        for (i = 0; i < n; i++) {
            if (graph[k][i] != 0 && colors[i] == colors[k]) {
                break;
            }
        }
        if (i == n) {
            return;
        }
    } while (true);
}//to get the next value of color of the graph
void mColoring(int k, int graph[][100], int n, int m) {//graph 
    do {
        nextVal(k, n, m, graph);

        if (colors[k] == 0) {
            return;
        } else {
            if (k == n) {
                for (int i = 0; i < n; i++) {
                    cout << colors[i] << " ";
                }
                cout << endl;
                return;
            } else {
                mColoring(k + 1, graph, n, m);
            }
        }
    } while (true);
}
int main() {
    int n, m;
    int graph[100][100] = {
        {0, 1, 0, 1},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 0}
    };
    n = 4;
    m = 3;
    mColoring(0, graph, n, m);
    return 0;
}
