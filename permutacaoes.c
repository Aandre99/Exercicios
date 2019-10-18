#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(x,y) (x < y) ? (x):(y)

typedef struct seg{
	int sum;
	int low;
}seg_tree;

int* A;
seg_tree* Seg;

void build(int i, int left, int right)
{
	if(left == right){
		Seg[i].sum = A[left];
		Seg[i].low = A[left];
		return;
	}
	else
	{
		int mid = (right+left)/2;
		build(2*i,left,mid);
		build(2*i+1,mid+1,right);

		Seg[i].sum = Seg[2*i].sum + Seg[2*i+1].sum;
		
		int a1 = Seg[2*i].low;
		int a2 = Seg[2*i+1].low;
		
		Seg[i].low = (A[a1] < A[a2]) ? a1:a2;

	}
}
int Sum(int i, int left, int right, int x, int y)
{
	if(left > y || right < x){
		return 0;
	}
	if(left >= x && right <= y){
		return Seg[i].sum;
	}
	else
	{
		int mid = (right+left)/2;
		return Sum(2*i,left,mid,x,y) + Sum(2*i+1,mid+1,right,x,y);
	}	
}

int small_Value(int i, int left, int right, int x, int y)
{
	if(left > y || right < x){
		return INT_MAX;
	}
	if(left >= x && right <= y){
		return Seg[i].low;
	}
	else
	{
		int mid = (right+left)/2;
		return min(small_Value(2*i,left,mid,x,y),small_Value(2*i+1,mid+1,right,x,y);
		
	}	
}
void modify(int i, int pos, int value, int left, int right)
{
	Seg[i].sum += (value - A[pos]);
  printf("Nova soma [%d,%d] = %d\n", left,right,Seg[i].sum);

	if(left == right){
		A[pos] = value;
    Seg[i].low = value;
	}
	else
	{
		int mid = (right+left)/2;
		if(pos < mid)
		{
			modify(2*i,pos,value,left,mid);
		}else
		{
			modify(2*i+1,pos,value,mid+1,right);
		}
		Seg[i].low = min(Seg[2*i].low,Seg[2*i+1].low);
	}
}
int main()
{
	int n,m,i, in1, in2;
	char Op;

	scanf("%d", &n);

	A = (int*)calloc(n,sizeof(int));
	Seg = (seg_tree*)calloc(4*n,sizeof(seg_tree));

	for ( i = 0; i < n; i++){
		scanf("%d", &A[i]);
	}

	build(1,0,n-1);

  int a = Sum(1,0,7,0,4);
  int b = small_Value(1,0,7,0,4);

  printf("Soma: %d , menor: %d", a,b);

	free(Seg);
	free(A);
	return 0;
}