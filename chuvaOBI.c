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
		Seg[i].low = min(Seg[2*i].low,Seg[2*i+1].low);

	}
}
int Sum(int i, int left, int right, int x, int y)
{
	if(y < left || right < x){
		return 0;
	}
	if(left >= x && right <= y){
		return Seg[i].sum;
	}
	else
	{
		int mid = (right+left)/2;
		return (Sum(2*i,left,mid,x,y) + Sum(2*i+1,mid+1,right,x,y));
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
void Query(int i, int left, int right, int x, int y, int* sumValue, int* smallValue)
{
	if(left > y ||  right < x){
		return;
	}
	if(left >= x && right <= y){
		*sumValue += Seg[i].sum;
		printf("somando mais %d\n", Seg[i].sum);
		*smallValue = min(*smallValue,Seg[i].low);
		return;
	}
	else
	{
		int mid = (right+left)/2;
		Query(2*i,left,mid,x,y,sumValue,smallValue);
		Query(2*i+1,mid+1,right,x,y,sumValue,smallValue);
	}
}
void modify(int i, int pos, int value, int left, int right)
{
	Seg[i].sum += (value - A[pos]);
	if(left == right){
		Seg[i].low = value;
        return ;
	}
	else
	{
		int mid = (right+left)/2;
		if(pos <= mid){
			modify(2*i,pos,value,left,mid);
		}else{
			modify(2*i+1,pos,value,mid+1,right);
		}

		int p1 = Seg[2*i].low;
		int p2 = Seg[2*i+1].low;

		Seg[i].low = (p1 < p2) ? p1:p2;
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

   	scanf("%d", &m);
	getchar();
	
	int k;

	for ( i = 0; i < m; i++)
	{
		scanf("%c%d%d",&Op,&in1, &in2);
		getchar();
		if(Op == 'Q'){

			int r1 = Sum(1,0,n-1,in1,in2);
			/*int r2 = small_Value(1,0,n-1,in1,in2);
		*/	
			int summ = 0, small = INT_MAX;
			Query(1,0,n-1,in1,in2,&summ,&small);
			printf("%d %d\n", r1, small);
		}
		else if(Op == 'U'){
			modify(1,in1,in2,0,n-1);
			/*printf("Soma\n");
			for ( k = 0; k < 4*n; k++){
			printf("%d ", Seg[k].sum);
			}
			printf("MENor\n");
			for ( k = 0; k < 4*n; k++){
			printf("%d ", Seg[k].low);
			}
			*/	
		}
	}

	free(Seg);
	free(A);
	return 0;
}