
#include <stdio.h>
#include "matmult.h"

/* C = A*B */
void matrixMultiply(int *matrixA, int *matrixB, int *matrixC, int m, int k, int n)
{
   /* IMPLEMENT ME */
    int b;
    for (int i=0;i<m;i++)
    {
     for (int j=0;j<n;j++)
     {
      matrixC[i*n+j]=0;
      for (int a=0;a<k;a++)
      {
       b=matrixA[i*k+a]*matrixB[a*n+j];
       matrixC[i*n+j]=matrixC[i*n+j]+b;
      }
     }
    }
}

void matrixPrint(int *matrix, int m, int k)
{
    int i, j;
    
    for (j = 0; j < m; j++)
    {
        for (i = 0; i < k; i++)
            printf("%d ", matrix[j*k+i]);
        printf("\n");
    }
}

