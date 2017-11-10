/*
*	NAME: 			YUTIKA CHANDRASHEKHAR KULWE
*	ROLL NO.: 		CED15I017
*	COURSE NAME:    Automata and Compiler Design
*	INPUT: 			DFA and a word
*	OUTPUT:			Accepted or not-accepted
*	USAGE:			cc DFA_Simulation_q1.c -o DFA_Simulation
*					./DFA_Simulation
*/


#include<stdio.h>
#include<stdlib.h>

//declaring the variables globally
int check(char b, int a);
int dfa[30][30],ip_symbols;
char sym[30];
char ip_string[30];

int main (void)
{
	int ip_states,ans,flag=0;	
	int final[30];
	
	//Taking input from the user
	//Total number of states
	printf("=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("Enter the number of states in the m/c\n");
	scanf("%d",&ip_states);
	
	//Numbe of input symbols
	printf("Enter the number of input symbols\n");
	scanf("%d",&ip_symbols);

	printf("Enter input symbols\n");

	for (int i = 0; i < ip_symbols; ++i)
	{
			scanf(" %c",&sym[i]);
	}
	//Displaying the input symbols
	for (int i = 0; i < ip_symbols; ++i)
	{
		//printf("i------->%d\n", i);
		if(i==0)
			printf(" \t %dnd input :\t %c\n",i+1,sym[i]);
			//printf("hcjdsvs\n");
		else if(i==1)
			printf(" \t %dnd input :\t %c\n",i+1,sym[i]);
		else if(i==2)
			printf(" \t %drd input :\t %c\n",i+1,sym[i]);
		else
			printf(" \t %dth input :\t %c\n",i+1,sym[i]);
	}

	//Input for Final states
	int final_states;
	printf("Enter the number of final states\n");
	scanf(" %d",&final_states);

	for (int i = 0; i < final_states; ++i)
	{
		if(i==0)
			printf(" \t %dst Final state :\t",i+1);
		else if(i==1)
			printf(" \t %dnd Final state :\t",i+1);
		else if(i==2)
			printf(" \t %drd Final state :\t",i+1);
		else
			printf(" \t %dth Final state :\t",i+1);

		scanf(" %d", &final[i]);
		printf("\n");
	}

	printf("-----------------------------------------------------------------------\n");
	printf("Define transition rule as ( initial state, input symbol ) = final state\n");

	for (int i = 0; i < ip_states; ++i)
	{
		for (int j = 0; j < ip_symbols; ++j)
		{
			printf("\n (q%d, %c) = q", i,sym[j]);
			scanf(" %d", &dfa[j][i]);
		}
	}

	//DISPLAY
	//You can uncomment the below part to display the DFA Table
	/*
	printf("-----------------------\n");
	printf("Displaying the table:\n");
	printf("\n States-input\n");
	for (int i = 0; i < ip_states; ++i)
	{
		printf("\t q%d\t", i);
		for (int j = 0; j < ip_symbols; ++j)
		{
			printf("q%d\t", dfa[j][i]);
		}
		printf("\n");
	}
	*/
	
	//Performing Check if the word is accepted by given DFA or not
	do
	{
		int st=0,k=0;
		printf("Input string:\n");
		scanf("%s", ip_string);
		while(ip_string[k]!='\0')
		{
			if((st=check(ip_string[k++],st))<0)
			{
				printf("Start %d \n", st);
				break;
			}
		}
		if(st!=-1)
		{
			for (int i = 0; i < final_states; ++i)
			{
				if(final[i]==st)
				{
				flag=1;
				printf("WORD ACCEPTED\n");
				}
			}
		}
		
		if(flag!=1)
		{
			printf("WORD NOT ACCEPTED\n");
		}
		flag=0;

		printf("Do you want to continue (1/0):\n");
		scanf(" %d", &ans);
	}while(ans==1);
	
	return(0);
}

//To check if the char in th estring exists as an input symbol or not
int check(char b, int a)
{
	for (int i = 0; i < ip_symbols; ++i)
	{
		if(b==sym[i])
		{
			return(dfa[i][a]);
		}
	}
	return -1;
}