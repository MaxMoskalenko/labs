
#include<stdio.h>



int main(){
    int n;
    double x,sum;
    sum = 1;



    printf("Enter a number of operands you want to compute: \n");
    scanf("%d",&n);



    printf("Enter operands(other than 1) in the entered quantity one after another: \n");



    for(int i = 1; i<=n ; i++){
        scanf("%lf",&x);
        while(x==1){
            printf("Uncomputable for x=1, try entering x other than 1: \n");
            scanf("%lf",&x);
        }
        sum *= (x*x)/(1-x);
    }
    printf("The output of  the entered operands: %.4lf", sum);



    return 0;
}
