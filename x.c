#include <stdio.h>
#include <stdlib.h>

int pot(int x, int n)
{
    if(n == 1){
        return x;
    }else
    {
        if(n % 2 == 0){
            int r = pot(x,n/2);
            return r*r;
        }else{
            int r = pot(x,(n-1)/2);
            return r * r * x;
        }
        
    }
    
}
int main(){

    int x, n;

    printf("Informe os valores para : x^n \n");
    printf("\n x: ");
    scanf("%d", &x);
    printf("n: ");
    scanf("%d", &n);

    printf("O resultado e': %d", pot(x, n));
    return 0;
}