#include <iostream>
#include <stack>
#include <chrono>
using namespace std;
using namespace chrono;
int Partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1, j = high;

    while (true) {
        while (i <= j && arr[i] <= pivot) i++;
        while (arr[j] > pivot) j--;

        if (i >= j) break;

        int temp = arr[i];//swap
        arr[i] = arr[j];
        arr[j] = temp;

        i++;
        j--;
    }
    arr[low] = arr[j];
    arr[j] = pivot;

    return j;
}

void QuickSort(int arr[], int low, int high) {
    stack<pair<int, int>> st; // Pair of (start, end) indices

    // push
    st.push(make_pair(low, high));

    while (!st.empty()) {
        low = st.top().first;
        high = st.top().second;
        st.pop();

        if (low < high) {
            int j = Partition(arr, low, high);
            st.push(make_pair(low, j - 1));
            st.push(make_pair(j + 1, high));
        }
    }
}

void PrintArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int createGraph1(){
    int avgtime=0;
    
    for(int i=1000;i<=100000;i+=1000){
        int total_time=0;
        int a[i];
        for (int k =1; k <=i; k++) 
             a[k]=rand()%i; 
        for(int j=1;j<=10;j++){
            auto start1 = high_resolution_clock::now();
            QuickSort(a, 0, i - 1);
            auto stop1 = high_resolution_clock::now();
            auto duration= duration_cast<microseconds>(stop1 - start1);
            total_time +=duration.count();
        }
        avgtime = total_time/10;
        cout<<i<<" "<<avgtime <<endl;
    }
}

int main() {
    createGraph1();

    return 0;
}
