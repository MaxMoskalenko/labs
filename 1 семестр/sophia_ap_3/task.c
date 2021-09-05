#include <stdio.h>
#include <locale.h>
#include <math.h>

int main()
{
  char* locale = setlocale(LC_ALL, "");
  int n = 2;
  double x, eps;

  printf("Лабораторна робота №3\n\n");
  printf("Введiть x: "); //введення x
  scanf("%lf", &x);
  printf("Введiть eps: ");
  scanf("%lf", &eps);

  double current = x;
  double S = 1 + x;

  do {
    current *= (x / n);
    S += current; //сума члені послідовності
    printf("n=%d, x=%6.3lf; ", n, current);
    n++;
} while (fabs(S - exp(x)) > eps);

  printf("\n\ne^x=%6.3lf\n", exp(x));
  printf("При x=%6.3lf, eps=%6.3lf, S=%6.3lf, n=%d", x, eps, S, n);

  return 0;
}
