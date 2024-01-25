#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
int sumn(int A[], int N) 
{ 
    if (N <= 0) 
        return 0; 
    return (A[N - 1]+sumn(A, N - 1)); 
};
int createGraph(){
    float avg_time =0;
 float total_time = 0;
    int s=0;
    for(int i=1000;i<=100000;i+=1000){
        int a[i];
        for (int k =1; k <=i; k++){
             a[k]=rand()%i;} 
        clock_t t1=clock();
        for (int j=1;j<=10;j++){
        clock_t t1=clock();
        s=sumn(a,i);
        clock_t t2=clock();
        total_time +=(t2-t1);
    }
    avg_time = total_time/10;
    cout<<i<<"  "<<avg_time<<endl;
}
};
int main(){
    createGraph();
    return 0;
}
