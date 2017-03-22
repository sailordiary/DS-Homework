#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char SElemType;
typedef int bool;
typedef int Status;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
} SqStack;

Status InitStack(SqStack *S) {
	S -> base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S -> base) exit(OVERFLOW);
	S -> top = S -> base;
	S -> stacksize = STACK_INIT_SIZE;
	
	return OK;
}

Status Push(SqStack *S, SElemType e) {
	if (S -> top-S -> base == S->stacksize) {
		S -> base = (SElemType *)realloc(S -> base, (S -> stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S -> base) exit (OVERFLOW);
		S -> top = S -> base + S -> stacksize;
		S -> stacksize += STACKINCREMENT;
	}
	*(S -> top++) = e;
	
	return OK;
}

Status Pop(SqStack *S, SElemType *e) {
	if (StackEmpty(S)) {
		printf("Empty stack\n");
		return ERROR;
	}
	*e = *(--S -> top);
	
	return OK;
}

bool StackEmpty(SqStack *S) {
	return (S -> top == S -> base)? TRUE: FALSE;
}

bool matchPattern(char s[]) {
	int i = 0;
	SqStack S;
	SElemType x;
	
	InitStack(&S);
	while (s[i] != '&' && s[i] != '@') {
		Push(&S, s[i]);
		i++;
	}
	if (s[i] == '@') return FALSE;
	++i;
	while (!StackEmpty(&S)) {
		Pop(&S, &x);
		if (x != s[i]) return FALSE;
		i++;
	}
	if (s[i] == '@') return TRUE;
	
	return FALSE;
}

int main() {
	char s[100];
	
	while (scanf("%s", &s) != -1)
		printf("%s\n", matchPattern(s)? "Match": "Mismatch");
	
	return 0;
}
