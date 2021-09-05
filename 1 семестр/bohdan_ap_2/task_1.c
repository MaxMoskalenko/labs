#include<stdio.h>
 
int main(){
    int n;
    double x;
    double sum = 0;

    printf("Enter a number of operands you want to add: \n");
    scanf("%d",&n);
    printf("Enter operands in the entered quantity one after another: \n");
 
    for(int i = 0; i<n ; i++){
        scanf("%lf",&x);
        sum+=x;
    }
 
    printf("The sum of the entered operands is: %.3lf",sum);
 
    return 0;
}
