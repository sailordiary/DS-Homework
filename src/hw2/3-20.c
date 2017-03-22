#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

#define SIZE 10

typedef int bool;
typedef int Status;

typedef struct{
	int x, y;
} PosType;

typedef struct{
	int color;
	bool visited;
	PosType seat;
} SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
} SqStack;

int m, n;

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

void FloodFill(SElemType image[SIZE][SIZE], PosType source, int fillColor) {
	SqStack s;
	InitStack(&s);
	SElemType e;
	int oldColor = image[source.x][source.y].color;
	
	Push(&s, image[source.x][source.y]);
	while (!StackEmpty(&s)) {
		Pop(&s, &e);
		source = e.seat;
		image[source.x][source.y].color = fillColor;
		image[source.x][source.y].visited = TRUE;

		if (source.x < m && !image[source.x+1][source.y].visited && image[source.x+1][source.y].color == oldColor)
			Push(&s, image[source.x+1][source.y]);
		if (source.x > 0 && !image[source.x-1][source.y].visited && image[source.x-1][source.y].color == oldColor)
			Push(&s,image[source.x-1][source.y]);
		if (source.y < n && !image[source.x][source.y+1].visited && image[source.x][source.y+1].color == oldColor)
			Push(&s, image[source.x][source.y+1]);
		if (source.y > 0 && !image[source.x][source.y-1].visited && image[source.x][source.y-1].color == oldColor)
			Push(&s, image[source.x][source.y-1]);
	}
}

void PrintImage(SElemType image[SIZE][SIZE]) {
	int i, j;
	
	printf("\n");
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			printf("%d ", image[i][j].color);
		printf("\n");
	}
}

int main() {
	int i, j;
	SElemType I[SIZE][SIZE];
	int fillColor;
	PosType source;
	
	for(i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			I[i][j].seat.x = i;
			I[i][j].seat.y = j;
			I[i][j].visited = 0;
			I[i][j].color = 0;
		}
	
	scanf("%d%d", &m, &n);
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &I[i][j].color);
	
	printf("\n");
	scanf("%d%d%d", &source.x, &source.y, &fillColor);
	
	FloodFill(I, source, fillColor);
	PrintImage(I);
	
	return 0;
}
