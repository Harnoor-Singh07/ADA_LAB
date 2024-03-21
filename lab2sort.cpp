#include<iostream>
#include<algorithm>
#include <chrono>
using namespace std;
using namespace chrono;

void merge(int a1[], int a2[], int result[], int s1, int s2) {
    int a = 0;
    int b = 0;
    int i = 0;

    while (a < s1 && b < s2) {
        if (a1[a] < a2[b]) {
            result[i] = a1[a];
            i++;
            a++;
        } else {
            result[i] = a2[b];
            i++;
            b++;
        }
    }

    while (a < s1) {
        result[i] = a1[a];
        i++;
        a++;
    }

    while (b < s2) {
        result[i] = a2[b];
        i++;
        b++;
    }
}
int createGraph1(){
    int avgtime=0;
    for(int i=1000;i<=100000;i+=1000){
        int total_time=0;
        int arr[i];
        int brr[i];
        for (int k = 0; k < i; k++) {
            arr[k] = rand() % i;
        }
        sort(arr, arr + i);

        for (int l = 0; l < i; l++) {
            brr[l] = rand() % i;
        }
        sort(brr, brr + i);

        int crr[i + i]; 
        for(int j=1;j<=10;j++){
            auto start1 = high_resolution_clock::now();
            merge(arr, brr,crr, i, i);
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