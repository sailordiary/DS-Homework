#include <stdio.h>
#define ERROR -1

int F(int n) {
	if (n < 0)
		return ERROR;

	int ans = 1;

	while (n > 0) {
		ans *= n;
		n = n/2;
	}

	return ans;
}

int main() {
	int n;
	
	for (n = 0; n < 10; n++)
		printf("F(%d) = %d\n", n, F(n));

	return 0;
}
