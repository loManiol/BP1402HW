#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

// allocate enough memory for matrix
void allocateMatrix(int*** matrix, int rows, int cols) {
    *matrix = (int**)malloc(rows * sizeof(int*));
	for (int i=0 ; i<rows ; i++)
	{
		(*matrix)[i] = (int*)malloc(cols * sizeof(int));
	}
}

// fill our matrix in order to be a Toeplitz matrix
void fillToeplitz(int** matrix, int n, int* ptr) {
	for (int i=0 ; i<n ; i++)
	{
		for (int j=0 ; j<n ; j++)
		{
            int x=j-i;

            if(i==0)
                matrix[i][j]=ptr[j];
            else if (j==0)
                matrix[i][j]=ptr[i+n-1];
            else
            {
                if(x>=0)
                {
                	matrix[i][j]=ptr[x];
				}
                else
                {
                    matrix[i][j]=ptr[(-1*x) + n - 1];
				}
            }     
		}
	}
}

// check elements f matrix
int checkMatrix(int** matrix, int i, int j){
    return matrix[i-1][j-1];
}

// printMatrix
void printMatrix(int** matrix, int rows, int cols) {
	for (int i=0 ; i<rows ; i++)
	{
		for (int j=0 ; j<cols ; j++)
		{
			printf ("%2d",matrix[i][j]);
		}
		printf ("\n");
	}
	printf ("\n");
}

// calculate determinant of our matrix
int determinantMatrix(int** matrix, int n) {
		if (n==1)
		return matrix[0][0];
	
	int det=0;
	int sign = 1;
	
	for (int c=0 ; c<n ; c++)
    {
		int** temp=(int**)malloc((n-1)*sizeof(int*));
		for (int r=0 ; r<n-1 ; r++)
			temp[r]=(int*)malloc((n-1)*sizeof(int));
		
		for (int i=0 ; i<n ; i++)
		{
			for (int j=0 ; j<n ; j++)
			{
				if (i!=0&&j!=c)
				{
					if (j>c)
						temp[i-1][j-1]=matrix[i][j];
					else
						temp[i-1][j]=matrix[i][j];
				}
			}
		}
		
		det += sign*matrix[0][c]*determinantMatrix(temp,n-1);
		
		sign *= -1;
		
		
		for (int r=0 ; r<n-1 ; r++)
			free(temp[r]);
    	free(temp);
    }
	return det;
}


// free the memory
void freeMatrix(int** matrix, int rows) {
	for (int i=0 ; i<rows ; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

