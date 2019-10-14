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
		Seg[i].low = left;
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
		return min(small_Value(2*i,left,mid,x,y),small_Value(2*i+1,mid+1,right,x,y));
	}	
}
void modify(int i, int pos, int value, int left, int right)
{
	Seg[i].sum += (value - A[pos]);

	if(left == right){
		A[pos] = value;
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

		int p1 = Seg[2*i].low;
		int p2 = Seg[2*i+1].low;
		Seg[i].low = (A[p1] < A[p2]) ? A[p1]:A[p2];
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
	
	for ( i = 0; i < n; i++){
		printf("%d ", A[i]);
	}
	
	build(1,0,n-1);
    
	scanf("%d", &m);
	getchar();
	for ( i = 0; i < m; i++)
	{
		scanf("%c%d%d",&Op,&in1, &in2);
		if(Op == 'Q'){

			int r1 = Sum(1,0,n-1,in1,in2);
			int r2 = small_Value(1,0,n-1,in1,in2);

			printf("%d %d\n", r1, A[r2]);
		}
		else{
			modify(1,in1,in2,0,n-1);
		}
	}
	free(Seg);
	free(A);
	return 0;
}