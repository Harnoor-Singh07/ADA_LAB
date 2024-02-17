#include<iostream>
#include<cstdlib>
#include<chrono>
using namespace std;
using namespace chrono;
void TT(char a[],int n , int k=0){
    if(k==n){
        for(int i=0;i<n;i++){
            cout<<a[i];
        }
        cout<<endl;
        return ;
    }
    else{
        a[k]='T';
        TT(a,n,k+1);
        a[k]='F';
        TT(a,n,k+1);
    }
}
int createGraph(){
     char a[10];
    int avgtime =0;
    int total = 0;
    for(int i=1;i<=10;i++){
    avgtime =0;
    total = 0;
    for (int m=0;m<10;m++){
    auto start = high_resolution_clock::now();
    TT(a,i);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total +=duration.count();
    }
    avgtime = total/10;
    cout<<"Avg time taken of array is "<<avgtime<<" microseconds"<<endl;
 }
}
int main(){
    createGraph();
    return 0;
}