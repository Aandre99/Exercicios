#include <stdio.h>
#include <stdlib.h>

#define max(x,y) (x > y) ? (x):(y)

int *A;
int *ST;
int *V;

void show(int* B, int left, int right)
{
    int i;
    for(i=left;i<right;i++)
    {
        printf("%d ", B[i]);
    }

}
void build(int i,int left, int right)
{
    if(left == right)
    {
        ST[i] = left;
        return;
    }
    else
    {
        int mid = (right+left)/2;
        build(2*i,left,mid);
        build(2*i+1,mid+1,right);

        int a1 = ST[2*i];
        int a2 = ST[2*i+1];

        ST[i] = (A[a1] > A[a2]) ? a1:a2;
    }
    
}
int query(int i, int left, int right, int x, int y)
{
    if(y < left || right < x){
        return -1;
    }
    if( x <= left && right <= y)
    {
        return ST[i];
    }
    else
    {
        int mid = (right+left)/2;
        int a1 = query(2*i,left,mid,x,y);
        int a2 = query(2*i+1,mid+1,right,x,y);

        if(a1 == -1) return a2;
        if(a2 == -1) return a1;         
        
        return (A[a1] > A[a2]) ? a1:a2;
    }
    
}
void divide_and_conquer(int left, int right,int big, int* cont, int size){

}
int main()
{
    int n, i, x;
    int cont=0;


    scanf("%d", &n);

    A = (int*)calloc(n,sizeof(int));
    V = (int*)calloc(n,sizeof(int));
    ST = (int*)calloc(4*n,sizeof(int));
    
    for (i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }

    build(1,0,n-1);
    //divide_and_conquer();
    show(ST,0,4*n);

    printf("%d", cont);
    free(A);
    free(ST);
    return 0;
}
