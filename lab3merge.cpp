#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
const int MAX_SIZE = 100000;
int b[MAX_SIZE];
void merge(int a[], int low, int mid, int high) {
    int h = low;
    int i = low;
    int j = mid + 1;

    while (h <= mid && j <= high) {
        if (a[h] <= a[j]) {
            b[i] = a[h];
            h++;
        } else {
            b[i] = a[j];
            j++;
        }
        i++;
    }

    if (h > mid) {
        for (int k = j; k <= high; k++) {
            b[i] = a[k];
            i++;
        }
    } else {
        for (int k = h; k <= mid; k++) {
            b[i] = a[k];
            i++;
        }
    }

    for (int k = low; k <= high; k++) {
        a[k] = b[k];
    }
}

void mergeSort(int a[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}
int createGraph(){
    int avgtime=0;
    int total_time=0;
    for(int i=1000;i<=100000;i+=1000){
        int a[i];
        for (int k =1; k <=i; k++) 
             a[k]=rand()%i; 
        for(int j=1;j<=10;j++){
            auto start1 = high_resolution_clock::now();
            mergeSort(a, 0, i-1);
            auto stop1 = high_resolution_clock::now();
            auto duration= duration_cast<microseconds>(stop1 - start1);
            total_time +=duration.count();
        }
        avgtime = total_time/10;
        cout<<"Avg time taken for array of "<<i<<" elements is"<<avgtime<<" microseconds"<<endl;
    }
}
int main() {
    createGraph();
    return 0;
}
