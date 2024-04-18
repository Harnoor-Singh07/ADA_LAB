#include <iostream>
#include <vector>
#include <algorithm>

#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Item {
    int weight;
    int profit;
};

// Sorting by profit/weight ratio in non-increasing order
bool compare(Item a, Item b) {
    double ratio1 = (double)a.profit / a.weight;
    double ratio2 = (double)b.profit / b.weight;
    return ratio1 > ratio2;
}

// Function to solve the Knapsack problem
double knapsack(int capacity, vector<Item>& items) {
    sort(items.begin(), items.end(), compare);
    double totalProfit = 0.0;
    int currentWeight = 0;
    for (const auto& item : items) {
        if (currentWeight + item.weight <= capacity) {
            totalProfit += item.profit;
            currentWeight += item.weight;
        } else {
            int remainingWeight = capacity - currentWeight;
            totalProfit += (double)item.profit * remainingWeight / item.weight;
            break;
        }
    }
    return totalProfit;
}

void createGraph(int numItems, int capacity) {
    vector<Item> items(numItems);

    // Generate random weights and profits for each item
    srand(time(0));
    for (int i = 0; i < numItems; ++i) {
        items[i].weight = rand() % (capacity / 2) + 1; // Limit weight to half the capacity
        items[i].profit = rand() % 100 + 1; // Random profit between 1 and 100
    }

    // Measure execution time
    auto start = high_resolution_clock::now();
    double maxProfit = knapsack(capacity, items);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Print the generated instance and the maximum profit
    cout << "Knapsack Capacity: " << capacity << endl;
    cout << "Items:" << endl;
    for (int i = 0; i < numItems; ++i) {
        cout << "Item " << i + 1 << ": Weight = " << items[i].weight << ", Profit = " << items[i].profit << endl;
    }
    cout << "Maximum Profit: " << maxProfit << endl;
    cout << "Execution Time: " << duration.count() << " milliseconds" << endl;
}

int main() {
    int numItems; // Number of items
    cout << "Enter the number of items: ";
    cin >> numItems;

    int capacity; // Capacity of the knapsack
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    createGraph(numItems, capacity);

    return 0;
}
