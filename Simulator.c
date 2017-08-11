/*
NAME:	 Simulator.c
PROGRAM: A C Program to generate a finite number of processes having random no. of 
		 interleaved I/O and CPU bursts of random duration using random number
		 generating function.
BY:		 Zaid Khan
COMPATIBLE COMPILER: GCC 4.5.2 with C/C++ 11 option selected.
*/

#include <stdio.h> 
#include <stdlib.h> 

//stdlib for srand() and rand().

int process[10][22]; 

//Global declaration of the array with 10 processes as the row number
//and 22 = 1 (PID) + 1 (Arrival Time) + 1 (Number of Bursts) + 19 (I/O and CPU
//bursts combined. 



/*This is the random generation function for Arrival Time calculation and 
Burst duration calculation*/
int randomnumberforAT (int i)
{
	srand(i); //Seed initialization
	int n = 0;
	do
	{
		n = rand() % 100; //Numbers will be from 1 - 100
	}while(n == 0); //To ensure no number generated is 0

	return n;
}


/*This is the random generation function for Number of CPU bursts*/
int randomnumber (int i)
{
	srand(i);

	int n = 0;
	do
	{
		n = rand() % 10;
	}while(n == 0);

	return n;
}

/*This is for assigning IDs to individual processes in sequential order*/
void ID_Assignment()
{
	for (int i = 0; i < 10; i++)
		process [i][0] = i + 1; 
}

//This is for assigning the Arrival Time to individual processes.
void Arrival_Assignment()
{
	int i;

	process [0][1] = 0;
	for (i = 1; i < 10; i++)
		process [i][1] = process [i - 1][1] + randomnumberforAT(i * i * i + 35);
		//The i 'cube' is just for adding salt i.e. making it more random.
		//35 is the sum of the individual digits of my birthdate.
}

//This is for assigning the No. of CPU bursts to each individual processes.
void NBurst_Assignment()
{
	int i;

	for (i = 0; i < 10; ++i)
		process [i][2] = randomnumber((i + 7) * (i + 17) * 35);
		//Prime numbers are ideal for introducing randomness
		//from what I've learned.
}


//This is for assigning random values to CPU/IO bursts of each individual processes.
void Burst_Assignment()
{
	int i, n;

	for (i = 0; i < 10; i++)
	{
		n = process [i][2] * 2 + 1; //Total number of Bursts = CPU burst * 2 + 1
		int j;
		for (j = 0; j < n; j++)
			process [i][3 + j] = randomnumberforAT (n * (i + 1) * (j + 1) + 35);
	}
}

//This is for display/printing the output.
void print()
{
	printf ("ID\tA. Time\t\tNo. of CPU Bursts\tBurst Duration\n");
	printf ("-----------------------------------------------------------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		printf ("P%d\t%dms\t\t%d\t\t", process [i][0], process [i][1], process [i][2]);
		int n = process [i][2];
		for (int j = 0; j < n * 2 + 1; j++)
			printf ("%d ", process[i] [3 + j]);
		printf("\n-----------------------------------------------------------------------\n");
	}
}

//Main function
int main()
{
	ID_Assignment();
	Arrival_Assignment();
	NBurst_Assignment();
	Burst_Assignment();
	print();
	return 0;
}