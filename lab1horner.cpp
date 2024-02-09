#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace chrono;
int horner(int a[],int n,int x)
{
    int sum = a[0]; 
    for (int i=1; i<n; i++) 
        sum = a[i]+sum*x ; 
 
    return sum; 
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
            int t = horner(a,i,2);
            auto stop1 = high_resolution_clock::now();
            auto duration= duration_cast<microseconds>(stop1 - start1);
            total_time +=duration.count();
        }
        avgtime = total_time/10;
        cout<<i<<" "<<avgtime <<endl;
    }
}
int main(){
    createGraph();
    

}
