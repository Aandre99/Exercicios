#include <stdio.h>

#define max(x,y) (x) > (y) ? (x):(y)
#define min(x,y) (x) < (y) ? (x):(y)

int index_Low = 10000;
int index_Hight = 0;

int binarySearch(int* v, int left, int right, int value){
	
	if(left == right){
		if(v[left] == value){
			return left;
		}
		return 0;
	}
	else
	{
		int mid = (right+left)/2;
		
		if(v[mid] < value && v[mid+1] > value)
		{
			index_Low = mid+1;
			index_Hight = mid;
		}
		else if(v[mid] > value)
		{
			index_Low = fmin(index_Low,binarySearch(v,left,mid,value);
			index_Hight = fmax(index_Hight,binarySearch(v,left,mid,value);
			
		}
		else
		{
			index_Hight = fmax(index_Hight,binarySearch(v,mid+1,right,value));
			index_Low = fmin(index_Low,binarySearch(v,mid+1,right,value));
		}
		
	}
}
int main(){
	
	int vector_size;
	int test_size, i,input;
	scanf("%d", &vector_size);
	
	int vector[vector_size];
	
	for(i=0;i<vector_size;i++){
		scanf("%d", &vector[i]);
	}
	
	scanf("%d", &test_size);
	
	for(i=0;i<test_size;i++)
	{
		scanf("%d",&input);
		binarySearch(vector,0,vector_size-1,input);
		printf("%d %d\n", index_Low, index_Hight);
	}
	return 0;
}