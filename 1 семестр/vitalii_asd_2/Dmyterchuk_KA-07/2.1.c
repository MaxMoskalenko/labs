#include <stdio.h>
#include <string.h>

int main() {
	int n = 3;
	int x = 257;
	char number[20] = { 0 };
	int k = 0;

	while (x >= n) {
		int r = x % n;
		number[k] = r + '0';

		x = x / n;
		k++;
	}
	number[k] = x + '0';
	printf("Result: ");
	while (k >= 0) {
		printf("%c", number[k]);
		k--;
	}

	return 0;
}