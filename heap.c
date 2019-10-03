#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printVetor(int* v,int ini ,int fim){

	int i;
	for(i=ini;i<=fim;i++)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

void merge(int* v, int ini, int meio, int fim){

	int tam = (fim - ini + 1),i = 0;
	int* vetorJuncao = (int*)calloc(tam,sizeof(int));
	int p1 = ini;
	int p2 = meio+1;
	
		while(p1 <= meio && p2 <= fim)
		{
			if(v[p1] < v[p2]){
				vetorJuncao[i] = v[p1++];
			}else{
				vetorJuncao[i] = v[p2++];
			}

			++i;
		}	
		while(p1 <= meio){
			vetorJuncao[i++] = v[p1++];
		}
		while(p2 <= fim){
			vetorJuncao[i++] = v[p2++];
		}

		for(i = ini ; i <= fim ; i++ ){
			v[i] = vetorJuncao[i-ini];
		}

	free(vetorJuncao);
}
void mergeSort(int* v, int ini, int fim){
	
	if(ini < fim){

		int meio = (fim+ini)/2;
		mergeSort(v,ini,meio);
		mergeSort(v,meio+1,fim);
		merge(v,ini,meio,fim);
	}
}

int main(){

	int n;
	int v[100], i;
	
	for(i=0;i<100;i++){
		scanf("%d", &v[i]);
	}
	int tam = 100;
	
	clock_t a = clock();
	mergeSort(v,0,tam-1);
	clock_t b = clock();
	printVetor(v,0,tam-1);
	
	printf("\n\n\n Merge: %.4lf s", (double)(b-a)/1000);
	return 0;
}