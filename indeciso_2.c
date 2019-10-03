#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define min(x,y) (x < y) ? (x):(y)

void showArray(int* v, int l, int r){

	int i;
	for(i=l;i<r;i++){
		printf("%d ", v[i]);
	}

	printf("\n");

}
void build_Segment(int* Array, int* Seg_Sum, int* Seg_Small, int index, int l, int r){

	if(r - l < 2)
	{
		Seg_Sum[index] = Array[l];
		Seg_Small[index] = Array[l];

		return;
	}
	else{

		int mid = (l+r)/2;
		build_Segment(Array,Seg_Sum,Seg_Small,index*2,l,mid);
		build_Segment(Array,Seg_Sum,Seg_Small,index*2+1,mid,r);
		
		Seg_Sum[index] = Seg_Sum[index*2] + Seg_Sum[index*2+1];
		Seg_Small[index] = min(Seg_Small[index*2],Seg_Small[index*2+1]);
	}
}

int sum(int* Seg_Sum, int l, int r , int index, int x, int y)
{
	if(x >= r || y <= l)
	{
		return 0;
	}
	if(x <= l && y >= r)
	{
		return Seg_Sum[index];
	}
	int mid = (l+r)/2;
	return  sum(Seg_Sum,l,mid,index*2,x,y) + sum(Seg_Sum,mid,r,index*2+1,x,y); 
}

int small(int* Array, int* Seg_Small, int l, int r , int index, int x, int y)
{
	if(x >= r || y <= l)
	{
		return -1;
	}
	if(x <= l && y >= r)
	{
		return Seg_Small[index];
	}
	int mid = (l+r)/2;
	int pos1 = small(Array,Seg_Small,l,mid,index*2,x,y);
	int pos2 = small(Array,Seg_Small,mid,r,index*2+1,x,y);

	if(pos1 == -1) return pos2;
	if(pos2 == -1) return pos1;

	return min(Array[pos1],Array[pos2]); 
}

void modify(int* v, int* Seg_Sum, int* Seg_Small, int pos, int value, int index, int l, int r)
{
	Seg_Sum[index] += ( value - v[pos]);

    if (r - l < 2)
    {
        v[pos] = value;
        return;
    }
    int mid = (l+r) / 2;
   
    if (pos < mid)
    {
        modify(v,Seg_Sum,Seg_Small,pos, value, index*2, l, mid);
    }
    else
    {
        modify(v,Seg_Sum,Seg_Small,pos, value, index*2+1, mid, r);
    }

    Seg_Small[index] = min(v[Seg_Small[index*2]], v[Seg_Small[index*2+1]]);
}
int main(){
	
	int size_array,size_seg,size_test, input1,input2, i;
	char Op;

	scanf("%d", &size_array);
	
	size_seg = 2*pow(2,log2(size_array)) - 1;

	int Array[size_array];
	int* Segment_Sum = (int*)calloc(size_seg,sizeof(int));
	int* Segment_Small = (int*)calloc(size_seg,sizeof(int));


	for (i = 0; i < size_array; ++i)
	{
		scanf("%d", &Array[i]);
	}

	build_Segment(Array,Segment_Sum,Segment_Small,1,0,size_array);

	scanf("%d", &size_test);

	showArray(Segment_Sum,1,size_seg);
	for(i=0;i<size_test;i++)
	{
		scanf("%c%d%d", &Op, &input1, &input2);
		printf("%c %d %d\n", Op, input1, input2);
		/*int SMALL, SUM;

		if(Op == 'Q')
		{
			SUM = sum(Segment_Sum,1,size_seg,1,input1,input2);
			SMALL  = small(Array,Segment_Small,1,size_seg,1,input1, input1);
		}
		/*else if(Op == 'U')
		{
			modify(Array, Segment_Sum,Segment_Small,input1,input2,1,1,size_array);

			SUM = sum(Segment_Sum,1,size_seg,1,input1,input2);
			SMALL  = small(Array,Segment_Small,1,size_seg,1,input1, input1);
		}*/

	}
	free(Segment_Sum);
	free(Segment_Small);

	return 0;
}