#include<stdio.h>



int factorial(int a){
    int factA;
    if(a==1){
        factA = a;
        return factA;
    }
    else{
        factA = a;
        return factA*factorial(factA-1);
    }
}



int main(){
    int n,m,C;



    printf("Enter natural values of n and m respectively to compute C(n,m): \n");
    scanf("%d %d",&n,&m);
    while(n<m){
        printf("Uncomputable, try entering values of n and m so that n>m: \n");
        scanf("%d %d",&n,&m);
    }



    C = factorial(n)/(factorial(n-m)*factorial(m));



    printf("C(n,m) for entered n and m is: %d",C);



    return 0;
}
