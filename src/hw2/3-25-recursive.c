#include <stdio.h>
#define ERROR -1

int F(int n) {
	if (n < 0)
		return ERROR;
	if (n == 0)
		return n+1;
	
	return n * F(n/2);
}

int main() {
	int n;
	
	for (n = 0; n < 10; n++)
		printf("F(%d) = %d\n", n, F(n));

	return 0;
}
