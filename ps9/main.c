
#include <stdio.h>
#include <stdlib.h>
#include "matmult.h"


int main(int argc, char* argv[])
{
    const int m = 2;
    const int k = 2;
    const int n = 3;
 
    int A[2][2] = { {2, 4}, {-1, 3} };
    int B[2][3] = { {-1, 2, -2}, {5, 3, -1} }; 
    int C[m][n];   

 
    matrixMultiply((int *)A, (int *)B, (int *)C, m, k, n);

    printf("A:\n");

    matrixPrint((int *)A, m, k);

    printf("\nB:\n");

    matrixPrint((int *)B, k, n);

    printf("\nC:\n");

    matrixPrint((int *)C, m, n);
    
    return EXIT_SUCCESS;
}


