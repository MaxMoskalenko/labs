#include <stdio.h>
#include <math.h>

int main() {
	int n = 3;
	int x = 100112;
	int sum = 0;
	int i = 0;

	while (x > 0) {
		int r = x % 10;
		x = (int)x / 10;
		sum += r * pow(n, i);
		i++;
	}

	printf("Result: %i", sum);
	return 0;
}