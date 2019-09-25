#include <stdio.h>

void encontraIndices(int* v, int esquerda, int direita,int valor,int* indiceMenor, int* indiceMaior){

	if(esquerda == direita)
	{
		if(valor)
		{
			*indiceMenor = esquerda;
			*indiceMaior = esquerda-1;
		}
		return;
	}
	else
	{
		int meio = (direita+esquerda)/2;
		*indiceMenor = meio;
		*indiceMaior = meio;

		if(valor == v[meio])
		{
			int i;
			for(i = meio; i >= esquerda;--i)
			{
				if(v[i] == valor)
				{
					*indiceMenor = i;
				}
			}

			for(i = meio+1;i<direita;i++)
			{
				if(v[i] == valor)
				{
					*indiceMaior = i;
				}
			}
		}
		if(valor < v[meio] && valor > v[meio-1])
		{
			*indiceMenor = meio;
			*indiceMaior = meio-1;
		}
		else if(valor > v[meio])
		{
			encontraIndices(v,meio+1,direita,valor,indiceMenor,indiceMaior);
		}
		else if(valor < v[meio])
		{
			encontraIndices(v,esquerda,meio,valor,indiceMenor,indiceMaior);
		}
	}
}
int main(){
	
	int n_casos,n_elementos,i,numero;

	scanf("%d", &n_elementos);

	int v[n_elementos], menorI=0,maiorI=0;

	for (i = 0; i < n_elementos; ++i)
	{
		scanf("%d", &v[i]);
	}

	scanf("%d", &n_casos);

	for (i = 0; i < n_casos; ++i)
	{
		scanf("%d", &numero);
		encontraIndices(v,0,n_elementos-1,numero,&menorI,&maiorI);
		printf("%d %d\n", menorI,maiorI);
		maiorI = 0;
		menorI = 0;

	}

	return 0;
}
