#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define FOUND 1
#define NONE 0

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

// assume the elements are of type int
typedef int ElemType;
typedef int Status;

typedef struct {
	ElemType *elem;
	int length;
	int listsize;
} SqList;

int precede(ElemType x, ElemType y) {
	return x < y;
}

Status InitList_Sq(SqList *L) {
	L -> elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L -> elem) exit(OVERFLOW);
	L -> length = 0;
	L -> listsize = LIST_INIT_SIZE;
	
	return OK;
}

void PrintList_Sq(SqList *L) {
	int i;
	
	for(i = 0; i < L -> length; i++)
		printf("%d ", L -> elem[i]);
	printf("\n");
}

Status LocateElem_Sq(SqList *L, ElemType e) {
	int i;
	
	if (precede(e, L -> elem[0]) || precede(L -> elem[L -> length-1], e)) return NONE;
	for (i = 0; i < L -> length && e != L -> elem[i]; i++)
		;
	return (i == L -> length)? NONE: FOUND;
}

// note that the list is only non-decreasing so there may be multiple occurences
Status DeleteElem_Sq(SqList *L, ElemType e) {
	int i = 0, l, r;
	
	if (precede(e, L -> elem[0]) || precede(L -> elem[L -> length-1], e)) return OK;
	for (i = 0; (i < L -> length) && (e != L -> elem[i]); i++)
		;
	if (i == L -> length) return OK;
	l = i;
	while (e == (L -> elem[i]) && i < L -> length) i++;
	r = i;
	L -> length = L -> length - r + l;
	for (i = l; i < L -> length; i++)
		L -> elem[i] = L -> elem[i+(r-l)];
	
	return OK;
}

Status RemoveMutual_Sq(SqList *A, SqList *B, SqList *C) {
	int i;
	
	for(i = 0; i < B -> length; i++)
		if (LocateElem_Sq(C, B -> elem[i]) == FOUND) DeleteElem_Sq(A, B -> elem[i]);
	return OK;
}

void DestroyList_Sq(SqList *L) {
	free(L);
}

int main() {
	SqList A, B, C;
	int a[] = {1, 2, 3, 4, 5, 6, 7, 7};
	int b[] = {0, 2, 3, 4, 6, 7, 9, 9};
	int c[] = {1, 2, 3, 6, 7, 8, 9, 9};
	
	if (InitList_Sq(&A) && InitList_Sq(&B) && InitList_Sq(&C)) {
		int i;
		
		for (i = 0; i < 7; i++) {
			A.elem[i] = a[i];
			B.elem[i] = b[i];
			C.elem[i] = c[i];
		}
		A.length = 7;
		B.length = 7;
		C.length = 7;
		PrintList_Sq(&A);
		PrintList_Sq(&B);
		PrintList_Sq(&C);
	}
	else {
		printf("Error");
		exit(ERROR);
	}
	
	RemoveMutual_Sq(&A, &B, &C);
	PrintList_Sq(&A);
	DestroyList_Sq(&A);
	DestroyList_Sq(&B);
	DestroyList_Sq(&C);
	
	return 0;
}
