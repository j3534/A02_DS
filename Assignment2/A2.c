/*
* FILE			    : A2.c
* PROJECT	        : Assignment 2 - Stacks and Queues using Linked Lists
* PROGRAMMER		: Justin Li
* FIRST VERSION		: 10/31/2026
* DESCRIPTION		:
*	This file contains the code for the program's entire functionality
*/

#pragma warning(disable:4996)

#include <stdio.h>

/*
* FUNCTION		    : main
* DESCRIPTION		:
*	Consumes all characters in the input buffer
* PARAMETERS		:
*	None
* RETURNS		    :
* 	void			: No return value
*/
void cleanInputBuffer() {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF) {}
}

/*
* FUNCTION		    : main
* DESCRIPTION		:
*	The entrypoint of the program
* PARAMETERS		:
*	None
* RETURNS		    :
* 	int 	    	: Whether the execution was successsful
*/
int main() {
	while (1) {
		printf("1. New web page\n");
		printf("2. Go backward\n");
		printf("3. Go forward\n");
		printf("4. Show current URL\n");
		printf("5. Show browsing history\n");
		printf("6. Exit browser\n");
		printf("\nChoose an action with a number: ");

		int number;
		if (scanf("%d", &number) == 0) {
			cleanInputBuffer();
			printf("Error: Please make sure you entered a number\n");
			continue;
		}

		switch (number) {
			case 1:

				break;
			case 2:

				break;
			case 3:

				break;
			case 4:

				break;
			case 5:

				break;
			case 6:

				break;
			default:
				printf("Error: There is no operation for the number: %d", number);
				break;
		}
	}

	return 0;
}