#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 			1
#define FALSE 		0

#define PI	 			3.14159265358979323846
#define DCT				8
#define DCT_DIV_2 DCT/2
#define QUANT			16

void print_matrix( double (*matrix)[DCT] )
{
	int i,j;
	for( i=0;i<DCT;i++ )
	{
		for( j=0;j<DCT;j++ )
		{
			printf( "%7.2f",matrix[i][j] );
		}
		printf("\n");
	}
} 

void print_coef( double (*matrix)[DCT_DIV_2] )
{
	int i,j;
	for( i=0;i<DCT_DIV_2;i++ )
	{
		for( j=0;j<DCT_DIV_2;j++ )
		{
			printf( "%7.2f",matrix[i][j] );
		}
		printf("\n");
	}
}

/* program starts here! */
int main( int argc, char *argv[] )
{
	// coefficients
	double coef[DCT];

	// grayscale image
	double dct1d[DCT][DCT] = { {0} };
	double dct2d[DCT][DCT] = { {0} };

	// wall clock time variables
	clock_t starttime;
	clock_t endtime;	

	// ROM initialization w/ cosine coefficients 
	int i,j;
	for( i=0;i<DCT;i++ )
	{
		coef[i] = 0.5*cos( (PI/16)*i );
	}
	
	// generating odd coefficient matrix
	double C_o[DCT_DIV_2][DCT_DIV_2] = { {coef[4],  coef[4],  coef[4],  coef[4]},
					{coef[2],  coef[6], -coef[6], -coef[2]},
					{coef[4], -coef[4], -coef[4],  coef[4]},
					{coef[6], -coef[2],  coef[2], -coef[6]} };

	// generating even coefficient matrix
 	double C_e[DCT_DIV_2][DCT_DIV_2] = { {coef[1],  coef[3],  coef[5],  coef[7]},
					{coef[3], -coef[7], -coef[1], -coef[5]},
					{coef[5], -coef[1],  coef[7],  coef[3]},
					{coef[7], -coef[5],  coef[3], -coef[1]} };

	//DEBUG
	printf("\n Even Coefficients: \n");
	print_coef( C_e );
	printf("\n Odd Coefficients: \n");
	print_coef( C_o );
	

	// input grayscale pixels
  double S[DCT][DCT] = { {182, 196, 199, 201, 203, 201, 199, 173},
        {175, 180, 176, 142, 148, 152, 148, 120},
        {148, 118, 123, 115, 114, 107, 108, 107},
        {115, 110, 110, 112, 105, 109, 101, 100},
        {104, 106, 106, 102, 104,  95,  98, 105},
        { 99, 115, 131, 104, 118,  86,  87, 133},
        {112, 154, 154, 107, 140,  97,  88, 151},
        {145, 158, 178, 123, 132, 140, 138, 133} };	

	// DEBUG
	printf("\nInput Matrix: \n");
	print_matrix( S );

	// start wall clock timer
	starttime = clock();	

	// calculate 1D DCT
	for( i=0;i<DCT;i++ )
	{
		// this inputs must be transposed
	  double X_o[DCT_DIV_2] = { S[0][i]+S[7][i], S[1][i]+S[6][i], S[2][i]+S[5][i], S[3][i]+S[4][i] };
		double X_e[DCT_DIV_2] = { S[0][i]-S[7][i], S[1][i]-S[6][i], S[2][i]-S[5][i], S[3][i]-S[4][i] };

		// DEBUG
		//printf("\n X_e: %5.0f %5.0f %5.0f %5.0f", X_e[0], X_e[1], X_e[2], X_e[3] );
		//printf("\n X_o: %5.0f %5.0f %5.0f %5.0f", X_o[0], X_o[1], X_o[2], X_o[3] );
	
		// Matrix multiplication of 
		// C_o*X_o (transposed)
		// C_e*X_e (transposed)
		for( j=0;j<DCT_DIV_2;j++ )
		{
			//even
			dct1d[i][j*2+1] += ( C_e[j][0]*X_e[0] + C_e[j][1]*X_e[1] + C_e[j][2]*X_e[2] + C_e[j][3]*X_e[3] );
			//odd
			dct1d[i][j*2] += ( C_o[j][0]*X_o[0] + C_o[j][1]*X_o[1] + C_o[j][2]*X_o[2] + C_o[j][3]*X_o[3] );
		}
	}	

	// DEBUG
	//printf("\n\n 1D-DCT Matrix: \n");
	//print_matrix( dct1d );

	// calculate 2D DCT
	for( i=0;i<DCT;i++ )
	{
		// this inputs must be transposed
		double X_o[DCT_DIV_2] = { dct1d[0][i]+dct1d[7][i], dct1d[1][i]+dct1d[6][i], dct1d[2][i]+dct1d[5][i], dct1d[3][i]+dct1d[4][i] };
		double X_e[DCT_DIV_2] = { dct1d[0][i]-dct1d[7][i], dct1d[1][i]-dct1d[6][i], dct1d[2][i]-dct1d[5][i], dct1d[3][i]-dct1d[4][i] };
	
		// DEBUG
		//printf("\n X_e: %5.0f %5.0f %5.0f %5.0f", X_e[0], X_e[1], X_e[2], X_e[3] );
		//printf("\n X_o: %5.0f %5.0f %5.0f %5.0f", X_o[0], X_o[1], X_o[2], X_o[3] );
	
		// Matrix multiplication of 
		// C_o*X_o (transposed)
		// C_e*X_e (transposed)
		for( j=0;j<DCT_DIV_2;j++ )
		{
			//even
			dct2d[i][j*2+1] += ( C_e[j][0]*X_e[0] + C_e[j][1]*X_e[1] + C_e[j][2]*X_e[2] + C_e[j][3]*X_e[3] );
			//odd
			dct2d[i][j*2] += ( C_o[j][0]*X_o[0] + C_o[j][1]*X_o[1] + C_o[j][2]*X_o[2] + C_o[j][3]*X_o[3] );
		}
	}	

// stop wall clock timer
	endtime = clock();
	

	// quantization
	for( i=0;i<DCT;i++ )
	{
		for( j=0;j<DCT;j++ )
		{
			dct2d[i][j] = dct2d[i][j]/QUANT;
		}
	}

		//DEBUG
	printf( "\n 2D-DCT Matrix: \n");
	print_matrix( dct2d );
	printf("Begin: %2.20f\n", (double) starttime );
	printf("End: %2.20f\n", (double) endtime);
	printf("\n\nElapsed time (seconds): %f\n",(double) (endtime-starttime)/CLOCKS_PER_SEC );
}
