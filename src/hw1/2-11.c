#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

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

// insert x into the non-decreasing list va while maintaining order
Status InsertElem_Sq(SqList *va, ElemType x) {
	if (va -> length == va -> listsize) {
		ElemType *newbase = (ElemType*)realloc(va -> elem, (va -> listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) return ERROR;
		va -> elem = newbase;
		va -> listsize += LISTINCREMENT;
	}
	
	int i;
	for (i = va -> length; (i > 0) && precede(x, va -> elem[i-1]); i--)
		va -> elem[i] = va -> elem[i-1];
	va -> elem[i] = x;
	++va -> length;
	
	return OK;
}

void PrintList_Sq(SqList *L) {
	int i;
	
	for(i = 0; i < L -> length; i++)
		printf("%d ", L -> elem[i]);
	printf("\n");
}

void DestroyList_Sq(SqList *L) {
	free(L);
}

// test case
int main(){
	SqList va;
	int a[] = {1, 2, 3, 5, 6, 7, 8};
	
	if (InitList_Sq(&va) != ERROR) {
		int i;
		for (i = 0; i < 7; i++)
			va.elem[i] = a[i];
		va.length = 7;
	}
	else {
		printf("Error");
		exit(ERROR);
	}
	// before insertion
	PrintList_Sq(&va);
	// after insertion
	if (InsertElem_Sq(&va, 4) != ERROR)
		PrintList_Sq(&va); 
	else printf("Insert failed");
	if (InsertElem_Sq(&va, 9) != ERROR)
		PrintList_Sq(&va);
	else printf("Insert failed");
	if (InsertElem_Sq(&va, 0) != ERROR)
		PrintList_Sq(&va);
	else printf("Insert failed");
	if (InsertElem_Sq(&va, -5) != ERROR)
		PrintList_Sq(&va);
	else printf("Insert failed");
	
	DestroyList_Sq(&va);
	
	return 0;
}
