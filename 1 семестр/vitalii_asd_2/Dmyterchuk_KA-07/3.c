#include <stdio.h>

int rec (int n){
	int x;
	if (n==0) {
		return 0;                   // что бы быть увер. что не будет отриц знач.
	}
	if(n>0) {
		if(n % 2 == 0) {
			x=3;                 // Если четное
		}
		else {
			x=2;                // Если нечетное
		}
		printf ("n = %i\n", n);   // Номер зайца, чет или не чет
		printf ("x = %i\n", x);   // Количетсво ушей
		return x+rec(n-1);        // Бер кол. уш. И происх рек для пред зайца
	}
}

int main (){
	int sum = rec(7);                    // точ. входа в рек
	printf("sum=%i", sum);              // сумма
	return 0;
}
