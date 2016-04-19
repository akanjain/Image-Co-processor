#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DCT				8
#define ZIGZAG_OUT	64
void print_matrix( int (*matrix)[DCT] )
{
	int i,j;
	for( i=0;i<DCT;i++ )
	{
		for( j=0;j<DCT;j++ )
		{
			printf( "%7d",matrix[i][j] );
		}
		printf("\n");
	}
} 

int main( int argc, char *argv[] )
{


	struct timeval  tv1, tv2;
	gettimeofday(&tv1, NULL);
 int QUANT[DCT][DCT] = { {65.94, 3.23, 0.07, -1.54, -0.75, -1.61, 0.75, 1.46},
        {7.10, 0.44, -0.87, 2.70, -0.38, 2.22, -0.84, -0.81},
        {12.22, 0.63, -0.54, -0.18, -1.81, -0.50, 0.05, 0.60},
        {2.24, -1.52, -0.97, -1.30, 0.73, -1.19, -0.53, 0.03},
        {2.55, -1.28, -0.85, 1.07, -0.89, 1.40, -0.31, -0.71},
        {0.45, -0.85, -0.47, -0.75, 1.14, -1.02, -0.09, -0.22},
        {-0.09, -0.83, -0.05, 0.08, 0.65, 1.00, 0.28, 0.07},
        {-0.42, -0.18, 0.26, 0.07, 0.66, -0.17, -0.20, 0.10} };

	int ZIGZAG[ZIGZAG_OUT];

		int i = 0;
    int j = 0;
    int k = 0;    
		int l;
//for upper triangle of matrix
    printf("%d, %d\t", i, j);
		ZIGZAG[k] = QUANT[i][j];
		k = k + 1;
    do
    {
        j++;
        printf("\n");
        printf("%d, %d\t", i, j);
				ZIGZAG[k] = QUANT[i][j];
				k = k + 1;
             
        while(j!=0)
        {
            i++;
            j--;
                 
        printf("%d, %d\t", i, j);
				ZIGZAG[k] = QUANT[i][j];
				k = k + 1;

            }
        i++;
        if(i>7)
        {
            i--;
            break;
        }
             
        printf("\n");
        printf("%d, %d\t", i, j);
				ZIGZAG[k] = QUANT[i][j];
				k = k + 1;

 
        while(i!=0)
        {
            i--;
            j++;
            printf("%d, %d\t", i, j);
						ZIGZAG[k] = QUANT[i][j];
						k = k + 1;

        }
    }
    while((i+j)<8);
         
//for lower triangle of matrix
    do
    {
        j++;
        printf("\n");
        printf("%d, %d\t", i, j);
				ZIGZAG[k] = QUANT[i][j];
				k = k + 1;

             
            while(j!=7)
        {
            j++;
            i--;
                 
            printf("%d, %d\t", i, j);
						ZIGZAG[k] = QUANT[i][j];
						k = k + 1;

        }
        i++;
        if(i>7)
        {
            i--;
            break;
        }
 
        printf("\n");
        printf("%d, %d\t", i, j);
				ZIGZAG[k] = QUANT[i][j];
				k = k + 1;
 
        while(i!=7)
        {
            i++;
            j--;
            printf("%d, %d\t", i, j);
						ZIGZAG[k] = QUANT[i][j];
						k = k + 1;
        }
    }
    while((i+j) >= 8);

		gettimeofday(&tv2, NULL);
	printf( "\n 2D-DCT Matrix: \n");
	print_matrix( QUANT );
	printf( "\n ZIGZAG Matrix Out: \n");
	for (l = 0; l < 64; l++)
	{
		printf ("%d\t",ZIGZAG[l]);
	}
	printf ("\n");
	printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
}
