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
* FUNCTION				: initializeStack
* DESCRIPTION			:
*	Creates a new stack
* PARAMETERS			:
*   None
* RETURNS				:
* 	struct Stack*  		: A pointer to the new stack
*/
struct Stack* initializeStack() {
	struct Stack* newStack = (struct Stack*)malloc(sizeof(struct Stack));
	if (newStack == NULL) {
		printf("Error: Failed to allocate memory for new stack\n");
		return NULL;
	}

	newStack->top = NULL;

	return newStack;
}

/*
* FUNCTION				: push
* DESCRIPTION			:
*	Pushes a new node onto the stack
* PARAMETERS			:
*   struct Stack* stack : The stack to push to
*	char* newUrl		: The url for the stack node
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
* FUNCTION				: freeStackNodes
* DESCRIPTION			:
*	Frees all memory within a stack
* PARAMETERS			:
*   struct Stack* stack : The stack to free
* RETURNS				:
*	void				: No return value
*/
void freeStackNodes(struct Stack* stack) {
	if (isEmpty(stack)) {
		return;
	}

	struct StackNode* current = stack->top;
	while (current != NULL) {
		struct StackNode* next = current->next;
	
		free(current);

		current = next;
	}

	stack->top = NULL;
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
* FUNCTION						: visitNewPage
* DESCRIPTION					:
*	Asks the user for the url of a new web page and adds it to history
* PARAMETERS					:
*	struct Stack* backStack		: The stack to push onto
*   struct Stack* forwardStack	: The stack to clear if needed
* RETURNS						:
* 	void						: No return value
*/
void visitNewPage(struct Stack* backStack, struct Stack* forwardStack) {
	printf("Enter the URL you want to visit: ");

	char urlBuffer[URL_MAX_LENGTH];
	fgets(urlBuffer, sizeof(urlBuffer), stdin);
	removeNewLine(urlBuffer);

	if (strlen(urlBuffer) == 0) {
		printf("Error: Cannot visit an empty URL\n");
		return;
	}

	push(backStack, urlBuffer);
	printf("You are now viewing the site: %s\n", urlBuffer);

	freeStackNodes(forwardStack);

	/*struct StackNode* current = backStack->top;
	while (current != NULL) {
		printf("Test: %s\n", current->url);
		current = current->next;
	}*/
}

/*
* FUNCTION						: viewBackward
* DESCRIPTION					:
*	Goes backward one url
* PARAMETERS					:
*	struct Stack* backStack		: The stack to pop off of
*	struct Stack* forwardStack	: The stack to push onto
* RETURNS						:
* 	void						: No return value
*/
void viewBackward(struct Stack* backStack, struct Stack* forwardStack) {
	if (isEmpty(backStack) || backStack->top->next == NULL) {
		printf("You have returned to the start of the current urls\n");
		return;
	}

	char* url = pop(backStack);
	push(forwardStack, url);

	printf("You are now viewing the page: %s\n", backStack->top->url);

	free(url);
}

/*
* FUNCTION						: viewForward
* DESCRIPTION					:
*	Goes forward one url
* PARAMETERS					:
*	struct Stack* backStack		: The stack to push onto
*	struct Stack* forwardStack	: The stack to pop off of
* RETURNS						:
* 	void						: No return value
*/
void viewForward(struct Stack* backStack, struct Stack* forwardStack) {
	if (isEmpty(forwardStack)) {
		printf("You have reached the end of the current urls\n");
		return;
	}

	char* url = pop(forwardStack);
	push(backStack, url);

	printf("You are now viewing the page: %s\n", backStack->top->url);

	free(url);
}

/*
* FUNCTION						: viewCurrent
* DESCRIPTION					:
*	Displays the current url
* PARAMETERS					:
*	struct Stack* backStack		: The stack containing the current page
* RETURNS						:
* 	void						: No return value
*/
void viewCurrent(struct Stack* backStack) {
	if (isEmpty(backStack)) {
		printf("You haven't viewed any pages yet\n");
		return;
	}

	char* url = peek(backStack);

	printf("You are currently viewing the page: %s\n", url);
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
	struct Stack* backStack = initializeStack();
	struct Stack* forwardStack = initializeStack();

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
				visitNewPage(backStack, forwardStack);
				break;
			case 2:
				viewBackward(backStack, forwardStack);
				break;
			case 3:
				viewForward(backStack, forwardStack);
				break;
			case 4:
				viewCurrent(backStack);
				break;
			case 5:

				break;
			case 6:
				freeStackNodes(backStack);
				freeStackNodes(forwardStack);

				free(backStack);
				free(forwardStack);

				printf("Goodbye\n");
				running = false;
				break;
			default:
				printf("Error: There is no operation for that number\n");
				break;
		}
	}

	return 0;
}