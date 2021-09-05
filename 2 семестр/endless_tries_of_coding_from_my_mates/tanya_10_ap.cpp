
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int main()
{
	int M = 3; // размеры
	int N = 4;
	int i;
	int** matrix;

//------

	matrix = new int* [M];
	for ( i = 0; i < M; i++) {
		matrix[i] = new int[N];
	}

//++++++

	for (i = 0; i < M; i++) {
		delete [] matrix[i];
	}

	delete [] matrix;

//--------
	return 0;


    void smallest(){
        int min = x[0][0];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (min >= x[i][j]) {
                    min = x[i][j];
                }
            }
        }
        cout << min;

    }
}
