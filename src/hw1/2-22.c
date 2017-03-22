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

// in-place reversal
Status ReverseList_L(LinkList *L) {
	LinkList p = (*L) -> next, q;
	
	(*L) -> next = NULL;
	while (p) {
		q = p;
		p = p -> next;
		q -> next = (*L) -> next;
		(*L) -> next = q;
	}
	
	return OK;
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
	
	if (ReverseList_L(&L) != ERROR)
		PrintList_L(&L);
	else {
		printf("Error");
		exit(ERROR);
	}
	DestroyList_L(&L);
	
	return 0;
}
