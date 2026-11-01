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

struct QueueNode {
	char url[URL_MAX_LENGTH];

	struct QueueNode* next;
};

struct Queue {
	struct QueueNode* front;
	struct QueueNode* rear;
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
* FUNCTION				: initializeQueue
* DESCRIPTION			:
*	Creates a new queue
* PARAMETERS			:
*   None
* RETURNS				:
* 	struct Queue*  		: A pointer to the new queue
*/
struct Queue* initializeQueue() {
	struct Queue* newQueue = (struct Queue*)malloc(sizeof(struct Queue));
	if (newQueue == NULL) {
		printf("Error: Failed to allocate memory for new queue\n");
		return NULL;
	}

	newQueue->front = NULL;
	newQueue->rear = NULL;

	return newQueue;
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
* FUNCTION				: isStackEmpty
* DESCRIPTION			:
*	Checks if a stack is currently empty
* PARAMETERS			:
*   struct Stack* stack : The stack to check
* RETURNS				:
*	bool				: Whether the stack is empty
*/
bool isStackEmpty(struct Stack* stack) {
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
	if (isStackEmpty(stack)) {
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
* FUNCTION				: peekStack
* DESCRIPTION			:
*	Returns the url at the top of the stack
* PARAMETERS			:
*   struct Stack* stack : The stack to read from
* RETURNS				:
*	char*				: The url of the top node
*/
char* peekStack(struct Stack* stack) {
	if (isStackEmpty(stack)) {
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
	if (isStackEmpty(stack)) {
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
* FUNCTION				: isQueueEmpty
* DESCRIPTION			:
*	Checks if a queue is currently empty
* PARAMETERS			:
*   struct Queue* queue : The queue to check
* RETURNS				:
*	bool				: Whether the queue is empty
*/
bool isQueueEmpty(struct Queue* queue) {
	return queue->front == NULL;
}

/*
* FUNCTION				: enQueue
* DESCRIPTION			:
*	Adds an item to the rear of the queue
* PARAMETERS			:
*   struct Queue* queue : The queue to add to
*	char* newUrl		: The url for the queue node
* RETURNS				:
* 	void 	    		: No return value
*/
void enQueue(struct Queue* queue, char* newUrl) {
	struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	if (newNode == NULL) {
		printf("Error: Failed to allocate memory for new node\n");
		return;
	}

	newNode->next = NULL;
	strcpy(newNode->url, newUrl);

	if (isQueueEmpty(queue)) {
		queue->front = newNode;
		queue->rear = newNode;
	}
	else {
		queue->rear->next = newNode;
		queue->rear = newNode;
	}
}

/*
* FUNCTION				: deQueue
* DESCRIPTION			:
*	Removes an item from the front of the queue
* PARAMETERS			:
*   struct Queue* queue : The queue to remove from
* RETURNS				:
*	char*				: The url of the front queue node
*/
char* deQueue(struct Queue* queue) {
	if (isQueueEmpty(queue)) {
		return NULL;
	}

	char* urlBuffer = (char*)malloc(sizeof(char) * URL_MAX_LENGTH);
	if (urlBuffer == NULL) {
		printf("Error: Failed to allocate memory for url\n");
		return NULL;
	}

	strcpy(urlBuffer, queue->front->url);

	struct QueueNode* currentFront = queue->front;
	queue->front = queue->front->next;

	if (queue->rear == currentFront) {
		queue->rear = NULL; // so that rear is not pointing to freed memory
	}

	free(currentFront);

	return urlBuffer;
}

/*
* FUNCTION				: peekQueue
* DESCRIPTION			:
*	Returns the url at the front of the queue
* PARAMETERS			:
*   struct Queue* queue : The queue to read from
* RETURNS				:
*	char*				: The url of the front queue node
*/
char* peekQueue(struct Queue* queue) {
	if (isQueueEmpty(queue)) {
		return NULL;
	}

	return queue->front->url;
}

/*
* FUNCTION				: freeQueueNodes
* DESCRIPTION			:
*	Frees all memory within a queue
* PARAMETERS			:
*   struct Queue* queue : The queue to free
* RETURNS				:
*	void				: No return value
*/
void freeQueueNodes(struct Queue* queue) {
	if (isQueueEmpty(queue)) {
		return;
	}

	struct QueueNode* current = queue->front;
	while (current != NULL) {
		struct QueueNode* next = current->next;

		free(current);

		current = next;
	}

	queue->front = NULL;
	queue->rear = NULL;
}

/*
* FUNCTION				: moveToQueueRear
* DESCRIPTION			:
*	Finds a url in the queue and moves it to the rear
* PARAMETERS			:
*   struct Queue* queue : The queue to read from
*	char* url			: The url to find
* RETURNS				:
*	void				: No return value
*/
void moveToQueueRear(struct Queue* queue, char* url) {
	if (isQueueEmpty(queue)) {
		return;
	}

	// do nothing if the rear is the url
	if (strcmp(queue->rear->url, url) == 0) {
		return;
	}
	
	if (strcmp(queue->front->url, url) == 0) {
		// re-link to the back if front is the url
		struct QueueNode* front = queue->front;

		queue->front = front->next;

		front->next = NULL;
		queue->rear->next = front;
		queue->rear = front;
	}
	else {
		struct QueueNode* previous = NULL;
		struct QueueNode* current = queue->front;

		while (current != NULL && strcmp(url, current->url) != 0) {
			previous = current;
			current = current->next;
		}

		if (current != NULL) {
			previous->next = current->next;
			free(current);

			enQueue(queue, url);
		}
	}
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
*   struct Queue* historyQueue  : The queue for managing history
* RETURNS						:
* 	void						: No return value
*/
void visitNewPage(struct Stack* backStack, struct Stack* forwardStack, struct Queue* historyQueue) {
	printf("Enter the URL you want to visit: ");

	char urlBuffer[URL_MAX_LENGTH];
	fgets(urlBuffer, sizeof(urlBuffer), stdin);
	removeNewLine(urlBuffer);

	if (strlen(urlBuffer) == 0) {
		printf("Error: Cannot visit an empty URL\n");
		return;
	}

	push(backStack, urlBuffer);
	enQueue(historyQueue, urlBuffer);

	printf("You are now viewing the site: %s\n", urlBuffer);

	freeStackNodes(forwardStack);
}

/*
* FUNCTION						: viewBackward
* DESCRIPTION					:
*	Goes backward one url
* PARAMETERS					:
*	struct Stack* backStack		: The stack to pop off of
*	struct Stack* forwardStack	: The stack to push onto
*   struct Queue* historyQueue  : The queue for managing history
* RETURNS						:
* 	void						: No return value
*/
void viewBackward(struct Stack* backStack, struct Stack* forwardStack, struct Queue* historyQueue) {
	if (isStackEmpty(backStack) || backStack->top->next == NULL) {
		printf("You have returned to the start of the current urls\n");
		return;
	}

	char* url = pop(backStack);
	push(forwardStack, url);

	printf("You are now viewing the page: %s\n", backStack->top->url);

	free(url);

	moveToQueueRear(historyQueue, backStack->top->url);
}

/*
* FUNCTION						: viewForward
* DESCRIPTION					:
*	Goes forward one url
* PARAMETERS					:
*	struct Stack* backStack		: The stack to push onto
*	struct Stack* forwardStack	: The stack to pop off of
*   struct Queue* historyQueue  : The queue for managing history
* RETURNS						:
* 	void						: No return value
*/
void viewForward(struct Stack* backStack, struct Stack* forwardStack, struct Queue* historyQueue) {
	if (isStackEmpty(forwardStack)) {
		printf("You have reached the end of the current urls\n");
		return;
	}

	char* url = pop(forwardStack);
	push(backStack, url);

	printf("You are now viewing the page: %s\n", backStack->top->url);

	free(url);

	moveToQueueRear(historyQueue, backStack->top->url);
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
	if (isStackEmpty(backStack)) {
		printf("You haven't viewed any pages yet\n");
		return;
	}

	char* url = peekStack(backStack);

	printf("You are currently viewing the page: %s\n", url);
}

/*
* FUNCTION						: viewHistory
* DESCRIPTION					:
*	Displays the history of urls
* PARAMETERS					:
*	struct Queue* historyQueue	: The queue containing the history of past urls
* RETURNS						:
* 	void						: No return value
*/
void viewHistory(struct Queue* historyQueue) {
	if (isQueueEmpty(historyQueue)) {
		printf("You haven't viewed any pages yet\n");
		return;
	}

	int urls = 1;
	printf("Current history:\n");

	struct QueueNode* current = historyQueue->front;
	while (current != NULL) {
		printf("%d. %s\n", urls, current->url);

		urls++;
		current = current->next;
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
	struct Stack* backStack = initializeStack();
	struct Stack* forwardStack = initializeStack();
	struct Queue* historyQueue = initializeQueue();

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
				visitNewPage(backStack, forwardStack, historyQueue);
				break;
			case 2:
				viewBackward(backStack, forwardStack, historyQueue);
				break;
			case 3:
				viewForward(backStack, forwardStack, historyQueue);
				break;
			case 4:
				viewCurrent(backStack);
				break;
			case 5:
				viewHistory(historyQueue);
				break;
			case 6:
				freeStackNodes(backStack);
				freeStackNodes(forwardStack);
				freeQueueNodes(historyQueue);

				free(backStack);
				free(forwardStack);
				free(historyQueue);

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