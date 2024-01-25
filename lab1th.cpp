#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
void move(int n,char source, char destination){
 cout<<"move disc : "<<n<<" from "<<source<<" to "<<destination<<endl; 
}
void TH(int n,char source, char spare , char destination){
    if(n==0)
    return;
    else{
        TH(n-1,source,destination,spare);
        move(n,source,destination);
        TH(n-1,spare,source,destination);
    }
    
};
int createGraph(){
float avg_time =0;
 float total_time = 0;
 for(int i=10;i<=100;i++){
    char source = 'A';
    char spare = 'B';
    char destination = 'C';
    for (int j=1;j<=10;j++){
    cout<<"trial : "<<j<<endl;
    clock_t t1=clock();
    TH(i,source,spare,destination);
    clock_t t2=clock();
    total_time +=(t2-t1);
    }
    avg_time = total_time/10;
    cout<<i<<"  "<<avg_time/CLOCKS_PER_SEC<<endl;
}
}
int main(){
 createGraph();
}