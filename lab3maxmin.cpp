#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
int maxVal, minVal;
void MaxMin(int a[], int i, int j) {
    if (i == j) {
        maxVal = minVal = a[i]; //single element
    } else if (i == j - 1) {
        //  two elements
        if (a[i] < a[j]) {
            maxVal = a[j];
            minVal = a[i];
        } else {
            maxVal = a[i];
            minVal = a[j];
        }
    } else {
        int mid = (i + j) / 2;
        int max1, min1;
        MaxMin(a, i, mid); // recursively find max and min in the first half
        int max2 = maxVal, min2 = minVal; 
        MaxMin(a, mid + 1, j); // recursively find max and min in the second half

        // Combine the results of two halves
        if (maxVal < max2)
            maxVal = max2;
        if (minVal > min2)
            minVal = min2;
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
            MaxMin(a, 0, i-1);
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
