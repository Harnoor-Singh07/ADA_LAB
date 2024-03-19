#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

int position(int arr[], int start, int end)
{
	int p = arr[start];
	int count = 0;
	for (int i = start+1; i <=end; i++) {
		if (arr[i] <= p)
			count++;
	}
	int index = start + count;
	swap(arr[index], arr[start]);
	int i = start, j = end;
	while (i < index && j > index) {
		while (arr[i] <= p) {
			i++;
		}
		while (arr[j] > p) {
			j--;
		}
		if (i < index && j > index) {
			swap(arr[i++], arr[j--]);
		}
	}
	return index;
}
int createGraph1(){
    int avgtime=0;
    int total_time=0;
    for(int i=1000;i<=100000;i+=1000){
        int a[i];
        for (int k =1; k <=i; k++) 
             a[k]=rand()%i; 
        for(int j=1;j<=10;j++){
            auto start1 = high_resolution_clock::now();
            int p = position(a, 0, i);
            auto stop1 = high_resolution_clock::now();
            auto duration= duration_cast<microseconds>(stop1 - start1);
            total_time +=duration.count();
        }
        avgtime = total_time/10;
        cout<<i<<" "<<avgtime <<endl;
    }
}
int main()
{
    createGraph1();
    return 0;
}