#include <stdio.h>
#define DEGREE 100

double eval(int *a, int n, double x0) {
	int i;
	double ans = (double)*a, power = 1.0;
	
	for (i = 1; i <= n; i++) {
		power *= x0;
		ans += *(a+i) * power;
	}
	
	return ans;
}

int main() {
	int n, a[DEGREE];
	double x0;
	
	int i;
	scanf("%d", &n);
	for (i = 0; i <= n; i++)
		scanf("%d", &a[i]);
	scanf("%lf", &x0);
	
	printf("%lf", eval(&a[0], n, x0));
	
	return 0;
}
