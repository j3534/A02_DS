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
#include <stdbool.h>
#include <string.h>

#define URL_MAX_LENGTH 50

/*
* FUNCTION		    : visitNewPage
* DESCRIPTION		:
*	Asks the user for the url of a new web page and adds it to history
* PARAMETERS		:
*	None
* RETURNS		    :
* 	void			: No return value
*/
void visitNewPage() {
	printf("Enter the URL you want to visit: ");

	char urlBuffer[URL_MAX_LENGTH];
	fgets(urlBuffer, sizeof(urlBuffer), stdin);
}

/*
* FUNCTION		    : cleanInputBuffer
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
	bool running = true;
	while (running) {
		printf("1. New web page\n");
		printf("2. Go backward\n");
		printf("3. Go forward\n");
		printf("4. Show current URL\n");
		printf("5. Show browsing history\n");
		printf("6. Exit browser\n");
		printf("\nChoose an action with a number: ");

		char menuInputBuffer[3] = { 0 };
		fgets(menuInputBuffer, sizeof(menuInputBuffer), stdin);

		// clean the input buffer if there is more in stdin
		if (strchr(menuInputBuffer, '\n') == NULL) {
			cleanInputBuffer();
		}

		int number;
		if (sscanf(menuInputBuffer, "%d", &number) == 0) {
			printf("Error: Please make sure you entered a number from 1 to 6\n");
			continue;
		}

		switch (number) {
			case 1:
				visitNewPage();
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
				printf("Goodbye");
				running = false;
				break;
			default:
				printf("Error: There is no operation for that number\n", number);
				break;
		}
	}

	return 0;
}