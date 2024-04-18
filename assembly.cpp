#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_STATIONS = 100;

int assemblyLine(int a[][MAX_STATIONS], int b[][MAX_STATIONS], int t[], int e[], int x[], int y[], int n) {
    // dp1[i]minimum time taken to reach station i on the first assembly line
    // dp2[i] reach station i on the second assembly line
    vector<int> dp1(n), dp2(n);

    // base case
    dp1[0] = e[0] + x[0];
    dp2[0] = e[1] + y[0];

    //minimum time for each station
    for (int i = 1; i < n; ++i) {
        dp1[i] = min(dp1[i - 1] + a[0][i], dp2[i - 1] + t[i - 1] + a[0][i]);
        dp2[i] = min(dp2[i - 1] + b[0][i], dp1[i - 1] + t[i - 1] + b[0][i]);
    }
    // Return the minimum time to reach the last station
    return min(dp1[n - 1] + x[n - 1], dp2[n - 1] + y[n - 1]);
}

int main() {
    int n; 
    cout << "Enter the number of stations: ";
    cin >> n;
    int a[2][MAX_STATIONS], b[2][MAX_STATIONS]; // Processing times for each station on the two assembly lines
    cout << "Enter processing times for assembly line 1: ";
    for (int i = 0; i < n; ++i) {
        cin >> a[0][i];
    }
    cout << "Enter processing times for assembly line 2: ";
    for (int i = 0; i < n; ++i) {
        cin >> b[0][i];
    }
    int t[MAX_STATIONS]; // Transition times between stations
    cout << "Enter transition times between stations: ";
    for (int i = 0; i < n - 1; ++i) {
        cin >> t[i];
    }
    int e[2]; // Entry times for each assembly line
    cout << "Enter entry times for assembly line 1 and 2: ";
    cin >> e[0] >> e[1];

    int x[MAX_STATIONS], y[MAX_STATIONS]; // Assignment of tasks to workstations
    cout << "Enter assignment of tasks to workstations for assembly line 1: ";
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    cout << "Enter assignment of tasks to workstations for assembly line 2: ";
    for (int i = 0; i < n; ++i) {
        cin >> y[i];
    }

    int fastestTime = assemblyLine(a, b, t, e, x, y, n);
    cout << "Minimum time to complete the product: " << fastestTime << endl;
    return 0;
}
