#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int * selectionSort(int a[],int n){
    for(int i=0;i<n;i++){
        int j=i;
        for(int k=i+1;k<n;k++){
            if(a[k]<a[j])
               j=k;
        }
    
        int t=a[i];
        a[i]=a[j];
        a[j]=t;
    }
    return a;
};
int createGraph(){
    int x[100],y[100],z=0;
    for(int i=1000;i<=100000;i+=1000){
        int a[i];
        for (int k =1; k <=i; k++) 
             a[k]=rand()%i; 
        clock_t t1=clock();
        for(int j=1;j<=10;j++)
            selectionSort(a,i);
        clock_t t2=clock();
        float avgtime=float(t2-t1)/10;
        x[z]=i;
        y[z]=avgtime;
        cout<<x[z]<<  " "<<y[z]<<endl;
        z++;

    }
}
int main(){
    createGraph();
    

}