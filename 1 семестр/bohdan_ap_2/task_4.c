#include<stdio.h>
#include<math.h>

int main(){
    int n;
    double minimal,x;

    printf("Enter from how many numbers a minimal element must be found: \n");
    scanf("%d",&n);
    printf("Enter numbers in entered quantity one after another: \n");
    scanf("%lf",&minimal);
    for(int i = 1; i<n; i++){
        scanf("%lf",&x);
        minimal = fmin(minimal,x);
    }
    printf("The minimal element among the entered number is: %.2lf",minimal);

    return 0;
}
