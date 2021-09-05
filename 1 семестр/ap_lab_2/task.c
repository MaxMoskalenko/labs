#include <stdio.h>
#include <math.h>
int main() {
    float a, min_x, max_x, dx;
    printf("Введіть константу a:\n");
    scanf("%f", &a);
    printf("Введіть межі для x: min_x та max_x\n");
    scanf("%f %f", &min_x, &max_x);
    printf("Введіть крок для x: dx\n");
    scanf("%f", &dx);

    for (float x = min_x; x <= max_x; x+=dx)
        if (x < 1.2 && a > 0)
            printf("x=%.1f y=%.4f\n", x, exp(x*x/2) + log(a));
        else if(x == 1.2)
            printf("x=%.1f y=%.4f\n", x, a*pow(cos(x*M_PI/2.7),3));
        else
            printf("x=%.2f y=%.4f\n", x, x*x + a*x + 5);

  return 0;
}
