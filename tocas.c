#include <stdio.h>
#include <stdlib.h>

int* visitados;
int* entrada;

void chuvaOBI(int inf, int sup, int* solucao)
{	
	int i;
	int maior = entrada[i];
	for(i = inf;i<sup;i++)
	{
		while(maior > entrada[i] && i < sup){
			(*solucao)++;
			++i;
		}
		printf("%d\n", entrada[i]);
		maior = entrada[i];
	}
}
int main(){
	
	int n,i, solucao=0;
	scanf("%d", &n);

	visitados = (int*)calloc(n,sizeof(int));
	entrada = (int*)malloc(n*sizeof(int));


	for(i=0;i<n;i++)
	{
		scanf("%d", &entrada[i]);
	}

	chuvaOBI(0,n,&solucao);

	printf("%d\n", solucao);
	return 0;
}