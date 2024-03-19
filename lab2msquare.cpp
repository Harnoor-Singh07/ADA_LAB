#include <iostream>
#include <iomanip>
#include<chrono>
using namespace std;
using namespace chrono;
void setMS(int** magicSquare, int n) {//To set all values of magicSquare matrix to zero
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            magicSquare[i][j] = 0;
        }
    }
}
void printMS(int** magicSquare, int n) {//Print matrix
    cout << "The Magic Square for n=" << n << ":\nSum of each row or column " << n * (n * n + 1) / 2 << ":\n\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(4) << magicSquare[i][j] << " ";
        cout << endl;
    }
}
void magicsquare(int n)
{
    int** magicSquare = new int*[n];//dynamic memory alloction for 2d array
    for (int i = 0; i < n; ++i) {
        magicSquare[i] = new int[n];
    }
    setMS(magicSquare, n);
    int i = n / 2; //initialize
    int j = n - 1;

    for (int element = 1; element <= n * n;) {
        if (i == -1 && j == n) // if both are out of bounds
        {
            j = n - 2;
            i = 0;
        }
        else {
            if (j == n)// if column is out of bounds
                j = 0;

            if (i < 0)// if row is out of bounds
                i = n - 1;
        }
        if (magicSquare[i][j]) // if the position already filled
        {
            j -= 2;
            i++;
            continue;
        }
        else
            magicSquare[i][j] = element++; //set the element then increment

        j++;
        i--;
    }
    printMS(magicSquare, n);

    for (int i = 0; i < n; ++i) {//free memory
        delete[] magicSquare[i];
    }
    delete[] magicSquare;
}
int createGraph(){
    int avgtime =0;
    int total = 0;
    for(int i=3;i<=100;i+=4){
		for (int m=0;m<10;m++){
			auto start = high_resolution_clock::now();
			magicsquare(i);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			total +=duration.count();
		}
		avgtime = total/10;
		cout<<"Avg time taken of array is "<<avgtime<<" microseconds"<<endl;
 	}
}
int main()
{
	createGraph();
    return 0;
}
