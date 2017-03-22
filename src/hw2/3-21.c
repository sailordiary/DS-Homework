#include <stdio.h>
#include <stdlib.h>

#define OPSETSIZE 7

#define OK 1
#define ERROR 0

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10


typedef struct Node{
	char data;
	struct Node* next;
} Node, *cur;

typedef struct {
	cur front;
	cur rear;
} LinkQueue;


typedef struct{
	char *base;
	char *top;
	int stacksize;
} SqStack;

typedef int Status;

Status InitQueue(LinkQueue *Q){
	Q -> front = Q -> rear = (cur)malloc(sizeof(Node));
	Q -> front -> next = NULL;
	return OK;
}


Status InitStack(SqStack *S){
	S -> base = (char*)malloc(STACK_INIT_SIZE*sizeof(char));
	S -> top = S -> base;
	S -> stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Pop(SqStack *S, char *e){
	if (S -> top == S -> base)
		return ERROR;
	*e = *--S -> top;
	return OK;
}

char GetTop(SqStack *S){
	if (S -> top == S -> base) {
		return '\0';
	}
	
	return *(S -> top-1);
}

Status Push(SqStack *S, char e){
	if (S -> top-S -> base >= S -> stacksize){
		S -> base = (char*)realloc(S -> base, (S -> stacksize+STACKINCREMENT) * sizeof(char));
		S -> top = S -> base+S -> stacksize;
		S -> stacksize += STACKINCREMENT;
	}
	
	*S -> top++ = e;
	return OK;
}

Status EnQueue(LinkQueue *Q, char e){
	cur p;
	
	p = (cur)malloc(sizeof(Node));
	p -> data = e;
	p -> next = NULL;
	Q -> rear -> next = p;
	Q -> rear = p;
	
	return OK;
}

Status DeQueue(LinkQueue *Q, char *e) {
	if (Q -> front == Q -> rear)
		return ERROR;
	cur p = Q -> front -> next;
	*e = p -> data;
	Q -> front -> next = p -> next;
	if (Q -> rear == p)
		Q -> rear = Q -> front;
	
	free(p);
	return OK;
}

char OPSET[OPSETSIZE] = {'+' , '-' , '*' , '/' , '(' , ')' , '#'};

char Prior[OPSETSIZE][OPSETSIZE] = {
	'>', '>', '<', '<', '<', '>', '>', 
	'>', '>', '<', '<', '<', '>', '>', 
	'>', '>', '>', '>', '<', '>', '>', 
	'>', '>', '>', '>', '<', '>', '>', 
	'<', '<', '<', '<', '<', '=', ' ', 
	'>', '>', '>', '>', ' ', '>', '>', 
	'<', '<', '<', '<', '<', ' ', '='
};

int ReturnOpOrd(char op, char* TestOp) {
	int i;
	
	for(i = 0; i< OPSETSIZE; i++) {
		if (op == TestOp[i])
			return i; }
	return -1;
}

char precede(char Aop, char Bop) {
	return Prior[ReturnOpOrd(Aop, OPSET)][ReturnOpOrd(Bop, OPSET)];
}

LinkQueue ReversePolish(char a[]) {
    int i = 0;
    char c = a[i], e;
    
    LinkQueue result;
    SqStack Op;
    InitQueue(&result);
    InitStack(&Op);
    Push(&Op, '#');
    while (c != '#' || GetTop(&Op) != '#') {
        if (ReturnOpOrd(c,OPSET) == -1) {
            EnQueue(&result, c);
            c = a[++i];
        }
        else
            switch (precede(GetTop(&Op), c)) {
                case '<':
                    Push(&Op, c);
                    c = a[++i];
                    break;
                case '=':
                    Pop(&Op,&e);
                    c = a[++i];
                    break;
                case '>':
                    Pop(&Op,&e);
                    EnQueue(&result, e);
                    break;
            }
    }
    return result;
}

int main() {
	char a[100] = "(a+b)*c-d#", ch;
	LinkQueue result = ReversePolish(a);
	
	while (result.front != result.rear) {
		DeQueue(&result, &ch);
		printf("%c", ch);
	}

	return 0;
}
