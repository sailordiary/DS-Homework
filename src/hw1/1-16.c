#include <stdio.h>

void swap(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void sort(int *x, int *y, int *z){
	if (*x < *y) swap(x, y);
	if (*x < *z) swap(x, z);
	if (*y < *z) swap(y, z);
}

int main(){
	int x, y, z;
	scanf("%d%d%d", &x, &y, &z);
	sort(&x, &y, &z);
	printf("%d %d %d", x, y, z);
	
	return 0;
}