#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXINT INT_MAX

const int arrsize = 100;

int main(){
	int i, k, a[arrsize];
	scanf("%d", &k);
	
	if (k > arrsize) {
		printf("Not enough space");
		exit(0);
	}
	for (i = 0; i < k; i++) {
		if (!i) a[i] = 1;
		else {
			if (a[i-1] > MAXINT / (2*i)) {
				printf("Overflow");
				exit(0);
			}
			a[i] = 2 * i * a[i-1];
		}
	}

	for (i = 0; i < k; i++)
		printf("%d ", a[i]);

	return 0;
}
