/*
NAME:	 SimulatorwithLL.c
PROGRAM: A C Program using link-list to generate a finite number of Processes having random no. of 
		 interleaved I/O and CPU Burst of random duration using random number
		 generating function.
BY:		 Zaid Khan
COMPATIBLE COMPILER: GCC 4.5.2.
*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>


/*This structure is for each individual bursts. Each burst consists of its time and the pointer 
  to the next burst since each process can have 'n'(variable) number of bursts. */
typedef struct Burst
{
	int bTime;
	struct Burst *next;
}Burst;


/*This structure is for each individual Process Data. Each Process Data consists of its PID, Arrival Time,
  Number of bursts and a pointer to its first burst which is of the type above. */
typedef struct ProcessData 
{
	int pID;
	int aTime;
	int nBurst;
	Burst *pBurstList;
}ProcessData;


/*This structure is for each individual Process. Each Process consists of its Data 
  and a pointer to the next Process. */
typedef struct node
{
	ProcessData data;
	struct node *next;
}Process;


//Method Declaration
Burst * CreateBursts(Process *);

Process * CreateElements()
{
	srand(time(NULL));
	Process *firstProcess, *P;
	int i = 0, arrivalTime = 0;
	

	firstProcess = (Process *)malloc(sizeof(Process)); //Memory allocation
	 
	firstProcess->data.pID = 1;
	firstProcess->data.aTime = arrivalTime;
	firstProcess->data.nBurst = rand() % 4 + 1;
	

	firstProcess->data.pBurstList = CreateBursts(firstProcess);

	firstProcess->next = NULL;

	P = firstProcess; 

	//Since we have already created the first process i is from 2 to n.(here in this case, 5)
	for (int i = 2; i <= 5; i++) 
	{
		
		P->next = (Process *)malloc(sizeof(Process));
		P = P->next;
		P->data.pID = i;
		arrivalTime += rand() % 9 + 1; //Cumulative
		P->data.aTime = arrivalTime;
		P->data.nBurst = rand() % 4 + 1;
		//Call to CreateBursts with the Process being passed as a pointer and the 
		//first burst address getting returned.
		P->data.pBurstList = CreateBursts(P); 
		P->next = NULL;
	}
	return firstProcess;
}



Burst * CreateBursts(Process *P)
{
		Burst *firstBurst = P->data.pBurstList = (Burst *)malloc(sizeof(Burst));
		Burst *temp = firstBurst;
		firstBurst->bTime = rand() % 9 + 1;
		for (int j = 1; j <= P->data.nBurst * 2; j++) //First burst created so j from 1 to n * 2
		{
			temp->next = (Burst *)malloc(sizeof(Burst));
			temp = temp->next;
			temp->bTime = rand() % 9 + 1;
			temp->next = NULL;
		}	
		return firstBurst;
}


void printLL(Process *head)
{
	while (head != NULL)
	{
		printf("PID : %d\n", head->data.pID);
		printf("Arrival Time : %d\n", head->data.aTime);
		printf("No. of Burst : %d\n", head->data.nBurst);
		Burst *h = head->data.pBurstList;
		
		printf("Bursts : ");
		while(h != NULL)
		{
			printf("%d ", h->bTime);	
			h = h->next;
		}
		printf("\n--------------------------------------------\n");
		head = head->next;
	}
}

int main()
{
	Process *Phead;
	Phead = CreateElements();
	printLL(Phead);
	return 0;
}

