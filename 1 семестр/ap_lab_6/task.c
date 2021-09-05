#include <stdio.h>
#include <math.h>


float find_sum(int n);

int main() {
    int n;
    printf("Введіть n - натуральне число: ");
    scanf("%i", &n);

    printf("Сума послідовності дорівнює:\n");
    printf("%g\n", find_sum(n));

    return 0;
}

float find_sum(int n) {
    float cur_x = 1.0, cur_y = 1.0, sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += cur_x / (1+ fabs(cur_y));
        cur_y = cur_y + cur_x;
        cur_x = 0.3 * cur_x;
    }
    return sum;
}
