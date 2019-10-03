#include <stdio.h>

#define max(x,y) (x > y) ? (x):(y)
#define min(x,y) (x < y) ? (x):(y)

int index_low = 0;
int index_high = 0;

void divide_And_Conquer(int* Array, int l, int r, int v)
{
	if(l == r){
	
		if(Array[l] >= v)
		{
			index_low = min(index_low,l);
		}
		if(Array[l] <= v)
		{
			index_high = max(index_high,l);
		}
		return;
	}
	else
	{
		int mid = (l+r)/2;
		divide_And_Conquer(Array,l,mid,v);
		divide_And_Conquer(Array,mid+1,r,v);
	}
}
void BinarySearch(int* Array, int l, int r, int v)
{
	if(l == r)
	{
		return;
	}
	else
	{
		int mid = (l+r)/2;
		if(Array[mid] == v)
		{
			index_low = mid;
			index_high = mid;

			divide_And_Conquer(Array,l,mid,v);
			divide_And_Conquer(Array,mid+1,r,v);
		}
		else if(Array[mid] < v && v < Array[mid+1]){
			
			index_low = mid+1;
			index_high = mid;
		}
		else
		{
			if(Array[mid] > v)
			{
				BinarySearch(Array,l,mid,v);
			}
			else
			{
				BinarySearch(Array,mid+1,r,v);
			}
		}
	}
}
int main()
{
	int size_array,size_tests;
	int input, i;

	scanf("%d", &size_array);
	int Array[size_array];

	for (i = 0; i < size_array; ++i)
	{
		scanf("%d", &Array[i]);	
	}

	scanf("%d", &size_tests);

	for (i = 0; i < size_tests; ++i)
	{
			scanf("%d" ,&input);

			if(input > Array[size_array-1])
			{
				printf("%d %d\n", size_array-1, size_array-1);
			}else{
				BinarySearch(Array,0,size_array-1,input);
				printf("%d %d\n", index_low, index_high);
			}
	}
	return 0;
}