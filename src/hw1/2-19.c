#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

// assume the elements are of type int
typedef int ElemType;
typedef int Status;

typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

int precede(ElemType x, ElemType y) {
	return x < y;
}

int leq(ElemType x, ElemType y) {
	return x <= y;
}

Status InitList_L(LinkList *L) {
	*L = (LinkList)malloc(sizeof(LNode));
	if (*L == NULL) return ERROR;
	(*L) -> next = NULL;
	
	return OK;
}

Status CreateList_L(LinkList *L, int i) {
	LinkList p;
	
	p = (LinkList)malloc(sizeof(LNode));
	if (!p) return ERROR;
	p -> data = i;
	p -> next = (*L) -> next;
	(*L) -> next = p;
	
	return OK;
}

// delete all elements greater than mink and less than maxk
Status ListDeletebyBounds_L(LinkList *L, int mink, int maxk) {
	LinkList p = (*L) -> next, left, t;
	
	if (mink > maxk) return ERROR;
	if (precede(maxk, p -> data)) return OK;
	
	while (p && leq(p -> data, mink)) {
		left = p;
		p = p -> next;
	}
	if (p == NULL) return OK;
	
	while (p && precede(p -> data, maxk)) {
		t = p -> next;
		free(p);
		p = t;
	}
	left -> next = p;
	
	return OK;
}

Status PrintList_L(LinkList *L) {
	LinkList p = *L;
	
	while (p -> next != NULL) {
		p = p -> next;
		printf("%d ", p -> data);
	}
	printf("\n");
	
	return OK;
}

void DestroyList_L(LinkList *L) {
	free(*L);
}

int main() {
	LinkList L;
	int i;
	
	InitList_L(&L);
	for (i = 10; i > 0; i--) {
		if (CreateList_L(&L, i) != ERROR) continue;
		else {
			printf("Error");
			exit(ERROR);
		}
	}
	PrintList_L(&L);
	
	int mink, maxk;
	scanf("%d%d", &mink, &maxk);
	if (ListDeletebyBounds_L(&L, mink, maxk) != ERROR)
		PrintList_L(&L);
	else {
		printf("Error");
		exit(ERROR);
	}
	DestroyList_L(&L);
	
	return 0;
}
