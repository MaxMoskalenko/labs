#include<stdio.h>
#include<math.h>

void task(double epsX){
    int n = 1;
    double S = 1,eps,cur,x = 0.7,prValue;
    prValue = 1/(1+x*x);
    cur =1;
    do{
        //cur=powf(-1,n)*powf(x,2*n);
        cur*=((-x)*x);
        S+=cur;
        eps = S - prValue;
        n++;
    }while(fabs(eps)>epsX);
    printf("Precise value: %lf; For given %lf: S= %lf eps= %lf n= %d \n",prValue,epsX,S,eps,n);
}

int main(){
    double eps1,eps2;
    printf("Enter eps1 and eps2: \n");
    scanf("%lf%lf",&eps1,&eps2);

    task(eps1);
    task(eps2);

    return 0;
}
