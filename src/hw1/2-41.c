#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct {
	int coef;
	int exp;
} PolyTerm;

typedef struct PolyNode {
	PolyTerm data;
	struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;

Status CreatePoly(LinkedPoly *L, int n) {
	*L = (LinkedPoly)malloc(sizeof(PolyNode));
	if (*L == NULL) return ERROR;
	(*L) -> next = NULL;
	
	int i;
	LinkedPoly p, prev, q;
	
	for (i = 0; i <= n; i++) {
		p = (LinkedPoly)malloc(sizeof(PolyNode));
		if (!p) return ERROR;
		scanf("%d", &p -> data.coef);
		p -> data.exp = i;
		prev = *L;
		q = (*L) -> next;
		while (q && (q -> data.exp < p -> data.exp)) {
			prev = q;
			q = q -> next;
		}
		p -> next = q;
		prev -> next = p;
	}
	
	return OK;
}

Status PrintPoly(LinkedPoly *L) {
	LinkedPoly p;
	p = *L;
	printf("f(x) = ");
	while (p -> next) {
		if (p -> next -> data.coef)
			if (p -> next -> data.exp != 0)
				printf("%dx^%d%c", p -> next -> data.coef, p -> next -> data.exp, (p -> next -> next)? '+': ' ');
			else
				printf("%d%c", p -> next -> data.coef, (p -> next -> next)? '+': ' ');
		p = p -> next;
	}
	printf("\n");
	
	return OK;
}

Status DifferentiatePoly(LinkedPoly *L) {
	LinkedPoly p, q, t;
	
	q = *L;
	p = (*L) -> next;
	while (p) {
		if (p -> data.exp == 0) {
			t = p;
			p = p -> next;
			q -> next = p;
			free(t);
		}
		else {
			p -> data.coef *= p -> data.exp;
			--p -> data.exp;
			q = p;
			p = p -> next;
		}
	}
	
	return OK;
}

int main() {
	LinkedPoly P;
	int n;
	
	scanf("%d", &n);
	if (CreatePoly(&P, n) != ERROR) {
		PrintPoly(&P);
		DifferentiatePoly(&P);
		printf("\n");
		PrintPoly(&P);
	}
	else {
		printf("ERROR");
		exit(ERROR);
	}
	
	return 0;
}
