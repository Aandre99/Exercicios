#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Par(x) (x % 2 == 0) ? 1:0

#define Print(v,e,d) for(i = e;i<d;i++) printf("%d ", v[i]);

int* pares;
int* impares;


void construir(int* A, int i, int esq, int dir)
{
	if(dir - esq < 2)
	{
		if(Par(A[esq])){
			pares[i] = 1;
			impares[i] = 0;
		}else{
			pares[i] = 0;
			impares[i] = 1;
		}
		return;
	}
	else
	{
		int meio = (dir+esq)/2;

		construir(A,2*i,esq,meio);
		construir(A,2*i+1,meio,dir);

		pares[i] = pares[2*i] + pares[2*i+1];
		impares[i] = impares[2*i] + impares[2*i+1];
	}
}
int consulta(int* vetor, int e, int d, int i, int x, int y)
{
	if(e >= y || d <= x){
		printf("0\n");
		return 0;
	}
	if( e >= x && d <= y){
		printf("%d\n", vetor[i]);
		return vetor[i];
	}
	else
	{
		int meio = (d+e)/2;
		return consulta(vetor,e,meio,2*i,x,y) + consulta(vetor,meio,d,2*i+1,x,y);
	}
}
int main()
{
	int n,m,i, esq, dir, op;
	int tam = 0;

	scanf("%d", &n);
	n++;

	tam = 4*n;
	pares = (int*)calloc(tam,sizeof(int));
	impares = (int*)calloc(tam,sizeof(int));

	int v[n];
	v[0] = -1;
	for(i=1;i<n;i++)
	{
		scanf("%d", &v[i]);
	}
	construir(v,1,1,n);

	Print(pares,1,tam);
	printf("\n");
	Print(impares,1,tam);
	scanf("%d", &m);

	for(i=0;i<m;i++)
	{
		scanf("%d%d%d", &op, &esq, &dir);

		if(op == 1){
			printf("%d\n", consulta(pares,1,tam,1,esq,dir));
		}
		else if(op == 2){
			printf("%d\n", consulta(impares,1,tam,1,esq,dir));
		}
	}
	return 0;
}
