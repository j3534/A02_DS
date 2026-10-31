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
#include <stdlib.h>

#define URL_MAX_LENGTH 50

struct StackNode {
	char url[URL_MAX_LENGTH];

	struct StackNode* next;
};

struct Stack {
	struct StackNode* top;
};

/*
* FUNCTION				: push
* DESCRIPTION			:
*	Pushes a new node onto the stack
* PARAMETERS			:
*   struct Stack* stack : The stack to push to
*	char* str			: The url for the stack node
* RETURNS				:
* 	void 	    		: No return value
*/
void push(struct Stack* stack, char* newUrl) {
	struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
	if (newNode == NULL) {
		printf("Error: Failed to allocate memory for new node\n");
		return;
	}

	newNode->next = stack->top;
	strcpy(newNode->url, newUrl);

	stack->top = newNode;
}

/*
* FUNCTION				: isEmpty
* DESCRIPTION			:
*	Checks if the stack is currently empty
* PARAMETERS			:
*   struct Stack* stack : The stack to check
* RETURNS				:
*	bool				: Whether the stack is empty
*/
bool isEmpty(struct Stack* stack) {
	return stack->top == NULL;
}

/*
* FUNCTION				: pop
* DESCRIPTION			:
*	Pops a node off the stack and returns the url
* PARAMETERS			:
*   struct Stack* stack : The stack to pop off of
* RETURNS				:
*	char*				: The url of the top node
*/
char* pop(struct Stack* stack) {
	if (isEmpty(stack)) {
		return NULL;
	}

	char* urlBuffer = (char*)malloc(sizeof(char) * URL_MAX_LENGTH);
	if (urlBuffer == NULL) {
		printf("Error: Failed to allocate memory for url\n");
		return NULL;
	}

	strcpy(urlBuffer, stack->top->url);

	struct StackNode* currentTop = stack->top;
	stack->top = stack->top->next;

	free(currentTop);

	return urlBuffer;
}

/*
* FUNCTION				: peek
* DESCRIPTION			:
*	Returns the url at the top of the stack
* PARAMETERS			:
*   struct Stack* stack : The stack to read from
* RETURNS				:
*	char*				: The url of the top node
*/
char* peek(struct Stack* stack) {
	if (isEmpty(stack)) {
		return NULL;
	}

	return stack->top->url;
}

/*
* FUNCTION		    : removeNewLine
* DESCRIPTION		:
*	Removes the first new line character from a string
* PARAMETERS		:
*	char* str		: The string to remove a new line from
* RETURNS		    :
* 	void 	    	: No return value
*/
void removeNewLine(char* str) {
	str[strcspn(str, "\n")] = '\0';
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
	removeNewLine(urlBuffer);

	if (strlen(urlBuffer) == 0) {
		printf("Error: Cannot visit an empty URL\n");
		return;
	}


}

/*
* FUNCTION		    : main
* DESCRIPTION		:
*	The entrypoint of the program
* PARAMETERS		:
*	None
* RETURNS		    :
* 	int 	    	: Whether the execution was successful
*/
int main() {
	bool running = true;
	while (running) {
		printf("----------------- Browser -----------------\n");
		printf("1. New web page\n");
		printf("2. Go backward\n");
		printf("3. Go forward\n");
		printf("4. Show current URL\n");
		printf("5. Show browsing history\n");
		printf("6. Exit browser\n");
		printf("-------------------------------------------\n");
		printf("Choose an action with a number: ");

		char menuInputBuffer[3] = { 0 };
		fgets(menuInputBuffer, sizeof(menuInputBuffer), stdin);

		// clean the input buffer if there is more in stdin
		if (strchr(menuInputBuffer, '\n') == NULL) {
			cleanInputBuffer();
		}

		removeNewLine(menuInputBuffer);

		if (strlen(menuInputBuffer) == 0) {
			printf("Error: Please make sure you entered a number from 1 to 6\n");
			continue;
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
				printf("Error: There is no operation for that number\n");
				break;
		}
	}

	return 0;
}