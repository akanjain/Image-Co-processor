#include "iostream"
#include <cstdlib>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

#define IDLE 0
#define DC_PROCESS 1
#define AC_PROCESS 2
#define OUTPUT 3
int zero = 0;
int *last_DC = &zero;
//*last_DC = 0;

int *rle(int zigzag[64], bool start, bool reset, int *enc_stream);
int *SizeOfNumber(int n[12]);
int *SizeOfNumberNeg(int n[12]);
//int *dec2bin(int c);
int *onesComplement(int n);
int *binaryTransform(int n,int b);

int main()
{	clock_t begin = clock();
	//struct timeval  tv1, tv2;
	//gettimeofday(&tv1, NULL);
	
	int *enc_stream = (int *)malloc(21*sizeof(int));
	//cout<<(*last_DC)<<endl;
	int test[64];
	srand(time(NULL));
	for (int i=0;i<10;i++)
	{
		test[i] = (rand() % 16) - 15;
		//cout<<test[i]<<" ";
	}
	for (int i=10;i<64;i++)
	{
		test[i] = 0;
		//cout<<test[i]<<" ";
	}
	//cout<<endl;
	
	int *result = rle(test, 1, 0, enc_stream);
	//cout<<endl;
	//gettimeofday(&tv2, NULL);
	clock_t end = clock();
	printf ("Total time = %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
	//printf ("Total time = %f seconds\n",
         //(double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         //(double) (tv2.tv_sec - tv1.tv_sec));
	//for (int i=0;i<21;i++)
		//cout<<result[i]<<" ";
		
	//cout<<endl;
	
	//result = rle(test, 1, 1, 0);
	//for (int i=0;i<64;i++)
		//cout<<result[i]<<" ";
	//cout<<endl;
	return 0;
}

int *rle(int zigzag[64], bool start, bool reset, int *enc_stream)
{
	int state = IDLE;
	int  *size;
	int reg[64][20];
	int index = 0;
	int counter = 0;
	int *amp;
	int *counter2;


	int defference_in_DC;
	int *binaryRepresentation;

	//while (!abort)
	//{
		if (reset) 
		{
			state = IDLE;
			for (int i=0;i<21;i++)
				enc_stream[i] = 0;//cout<<"i'm reseting, state is "<<state<<endl;
			//*enc_stream = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		}
		else if (start)
		{
			state = DC_PROCESS;//cout<<"i'm starting, state is "<<state<<endl;
		}
	
		if (state == IDLE)
		{
			for (int i=0;i<21;i++)
				enc_stream[i] = 0;//cout<<"state is IDLE"<<endl;
		}
		if (state == DC_PROCESS)
		{	//cout<<"state is DC_PROCESS"<<endl;
			defference_in_DC = zigzag[0] - *last_DC;
			if (defference_in_DC >= 0)
			{
				binaryRepresentation = binaryTransform(defference_in_DC, 12);
				amp = binaryRepresentation;
			}
			else
			{
				binaryRepresentation = binaryTransform((0 - defference_in_DC), 12);
				amp = onesComplement(defference_in_DC);
			}
				
			size = SizeOfNumber(binaryRepresentation);
			*last_DC = zigzag[0];
			
			//reg[index][0] = 1;
			for (int i=0;i<4;i++)
				reg[index][i] = 0;
			for (int i=4;i<8;i++)
				reg[index][i] = size[i-4];
			for (int i=8;i<20;i++)
				reg[index][i] = amp[i-8];

			//reg[index] = {1, 0,0,0,0,size, zigzag[0]};
			//reg[index][0] =size[0];
			//reg[index][1] =size[1];
			//reg[index][2] =size[2];
			//reg[index][3] =size[3];
			index++;
			state = AC_PROCESS;
		}
		if(state == AC_PROCESS)
		{	//cout<<"state is AC_PROCESS"<<endl;
			for(int i=1;i<64;i++)
			{
				if (zigzag[i] == 0)
					counter++;
				else
				{	
					counter2 = binaryTransform(counter, 4);
					if (zigzag[i]<0)
					{
						amp = onesComplement(zigzag[i]);
						size = SizeOfNumber(binaryTransform((0-zigzag[i]), 12));
					}
					else
					{
						amp = binaryTransform(zigzag[i], 12);
						size = SizeOfNumber(amp);
					}
					for (int i=0;i<4;i++)
						reg[index][i] = counter2[i];
					for (int i=4;i<8;i++)
						reg[index][i] = size[i-4];
					for (int i=8;i<20;i++)
						reg[index][i] = amp[i-8];
					//reg[index] = {1,counter2, size, amp};
					index++;
					counter = 0;
				}
				if (counter == 15)
				{
					counter2 = binaryTransform(counter, 4);
					for (int i=0;i<4;i++)
						reg[index][i] = counter2[i];
					for (int i=4;i<20;i++)
						reg[index][i] = 0;
					//reg[index] = {1,counter2, 0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0};
					index++;
					counter = 0;
				}
			}
			if (counter)
			{	//cout<<"Couter is not zero!"<<endl;
				counter2 = binaryTransform(counter, 4);
				for (int i=0;i<4;i++)
					reg[index][i] = counter2[i];
				for (int i=4;i<20;i++)
					reg[index][i] = 0;
				index++;
				//reg[index] = {counter2, 0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0};
			}
			state = OUTPUT;
		}
		//cout<<"index is "<<index<<"       "<<"state is "<<state<<endl;
		if (state == OUTPUT)
		{	//cout<<"state is OUTPUT"<<endl;
			enc_stream[0] = 1;
			for (int i=0;i<index;i++)
			{
				for (int j=1;j<21;j++)
				{
					enc_stream[j] = reg[i][j-1];
				}
				/*for (int j=0;j<21;j++)
				{
					cout<<enc_stream[j]<<" ";
				}
				cout<<endl;*/
			}
			//cout<<"begin to output end of stream"<<endl;
			enc_stream[0] = 1;
			for (int i=1;i<21;i++)
				enc_stream[i] = 0;
			//cout<<"output end of stream:"<<endl;
			/*for (int j=0;j<21;j++)
			{
				cout<<enc_stream[j]<<" ";
			}
				cout<<endl;*/
		}
		//cout<<"end"<<endl;
		for (int i=0;i<21;i++)
				enc_stream[i] = 0;
		/*for (int j=0;j<21;j++)
		{
			cout<<enc_stream[j]<<" ";
		}*/
		//cout<<endl;
		return enc_stream;
}

int *SizeOfNumber(int *n)
{
	int *size = (int *)malloc(4*sizeof(int));
	
	if (n[0])
	{
		size[0]=1;
		size[1]=1;
		size[2]=0;
		size[3]=0;
	}
	else if(n[1])
	{
		size[0]=1;
		size[1]=0;
		size[2]=1;
		size[3]=1;
	}
	else if(n[2])
	{
		size[0]=1;
		size[1]=0;
		size[2]=1;
		size[3]=0;
	}
	else if (n[3])
	{
		size[0]=1;
		size[1]=0;
		size[2]=0;
		size[3]=1;
	}
	else if (n[4])
	{
		size[0]=1;
		size[1]=0;
		size[2]=0;
		size[3]=0;
	}
	else if (n[5])
	{
		size[0]=0;
		size[1]=1;
		size[2]=1;
		size[3]=1;
	}
	else if (n[6])
	{
		size[0]=0;
		size[1]=1;
		size[2]=1;
		size[3]=0;
	}
	else if (n[7])
	{
		size[0]=0;
		size[1]=1;
		size[2]=0;
		size[3]=1;
	}
	else if (n[8])
	{
		size[0]=0;
		size[1]=1;
		size[2]=0;
		size[3]=0;
	}
	else if (n[9])
	{
		size[0]=0;
		size[1]=0;
		size[2]=1;
		size[3]=1;
	}
	else if (n[10])
	{
		size[0]=0;
		size[1]=0;
		size[2]=1;
		size[3]=0;
	}
	else
	{
		size[0]=0;
		size[1]=0;
		size[2]=0;
		size[3]=1;
	}
	return size;
}

int *onesComplement(int n)
{
	int *result = (int *)malloc(12*sizeof(int));
	int abs = 0-n;
	//int twosComplement = (abs^0x3fff)+1;
	int *p = binaryTransform(abs, 12);
	for (int i=0;i<12;i++)
	{
		result[i] = !p[i];
	}
	return result;
}

int *binaryTransform(int n,int b)
{	
	int tmp = n;
	int *result = (int *)malloc(b*sizeof(int));
	for (int i=0;i<b;i++)
	{
		if ((tmp % 2) == 0)
			result[b-i-1] = 0;
		else 
			result[b-i-1] = 1;
		
		tmp = tmp / 2;
	}
	return result;
}