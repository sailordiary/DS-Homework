#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define INCREMENT 10
#define STACK_INIT_SIZE 100

typedef int Status;

typedef struct Node {
	char data;
	struct Node *next;
} Node, *cur;

// this two-way list structure allows exiting on both sides
typedef struct{
	Node *front;
	Node *rear;
} TwoWayList;

Status Push(TwoWayList *S, char e) {
	cur p;
	
	p = (cur)malloc(sizeof(Node));
	p -> data = e;
	p -> next = NULL;
	S -> rear -> next = p;
	S -> rear = p;
	return OK;
}

Status DeFront(TwoWayList *S, char *e) {
	cur p;
	
	if (S -> rear == S -> front) return ERROR;
	p = S -> front -> next;
	*e = p -> data;
	S -> front -> next = p -> next;
	if (S -> rear == p)
		S -> rear = S -> front;
	free(p);
	
	return OK;
}

Status InitStack(TwoWayList *S) {
	S -> front = S -> rear =  (cur)malloc(sizeof(Node));
	S -> front -> next = NULL;
	
	return OK;
}

Status DeRear(TwoWayList *S, char *e) {
	cur p, prior = S -> front;
	
	if (S -> rear == S -> front) return ERROR;
	p = S -> rear;
	*e = p -> data;
	while (prior -> next != S -> rear) prior = prior -> next;
	S -> rear = prior;
	free(p);
	
	return OK;
}

// checks if a given string is a palindrome
Status isPalindrome(char a[]) {
	TwoWayList S;
	int i = 0;
	char f, r;
	
	InitStack(&S);
	for(; a[i] != '@'; i++)
		Push(&S, a[i]);
	
	while (S.rear != S.front) {
		DeFront(&S, &f);
		// length is odd
		if (S.rear == S.front) return OK;
		DeRear(&S, &r);
		if (f != r) return ERROR;
	}
	
	return OK;
}

int main() {
	char s[100];
	
	while (scanf("%s", &s) != -1)
		printf(isPalindrome(s)? "Yes\n": "No\n");
	
	return 0;
}
