#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define GREATER 1
#define EQUAL 0
#define LESS -1

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

// compare two sequential lists
Status CompareList_Sq(SqList *A, SqList *B) {
	int p = 0;
	
	while (A -> elem[p] == B -> elem[p]) {
		++p;
		if (p == A -> length)
			return (p == B -> length)? EQUAL: LESS;
	}
	if (precede(A -> elem[p], B -> elem[p]))
		return LESS;
	return GREATER;
}

void DestroyList_Sq(SqList *L) {
	free(L);
}

int main() {
	SqList L, M, N, O;
	int l[] = {1, 2, 3, 4, 5, 6, 7};
	int m[] = {1, 2, 3, 5, 6, 7, 8};
	int n[] = {1, 2, 3, 5, 6, 7, 8, 9};
	
	if (InitList_Sq(&L) && InitList_Sq(&M) && InitList_Sq(&N) && InitList_Sq(&O)) {
		int i;
		Status result;
		
		for (i = 0; i < 7; i++)
			L.elem[i] = l[i];
		L.length = 7;
		for (i = 0; i < 7; i++)
			M.elem[i] = m[i];
		M.length = 7;
		for (i = 0; i < 8; i++) {
			N.elem[i] = n[i];
			O.elem[i] = n[i];
		}
		N.length = 8;
		O.length = 8;
		
		printf("L %c M\n", ((result = CompareList_Sq(&L, &M)) == GREATER)? '>': (result == LESS)? '<': '=');
		printf("M %c N\n", ((result = CompareList_Sq(&M, &N)) == GREATER)? '>': (result == LESS)? '<': '=');
		printf("M %c L\n", ((result = CompareList_Sq(&M, &L)) == GREATER)? '>': (result == LESS)? '<': '=');
		printf("N %c O\n", ((result = CompareList_Sq(&N, &O)) == GREATER)? '>': (result == LESS)? '<': '=');
	}
	else {
		printf("Error");
		exit(ERROR);
	}
	
	return 0;
}
