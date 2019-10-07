#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Par(x) (x % 2 == 0) ? 1:0

#define Print(v,e,d) for(i = e;i<d;i++) printf("%d ", v[i]);
int* st;

//int* pares;
//int* impares;

#define left(a) (a << 1)
#define right(a) ((a << 1) | 1)
#define mid(a,b) (a + ((b-a) >> 1))


void construir(int* A, int i, int esq, int dir)
{
	if(dir == esq )
	{
		/*if(Par(A[esq])){
			pares[i] = 1;
			impares[i] = 0;
		}else{
			pares[i] = 0;
			impares[i] = 1;
		}*/

		st[i] = A[esq];
		return;
	}
	else
	{
		int meio = mid(esq,dir);

		construir(A,left(i),esq,meio);
		construir(A,right(i),meio+1,dir);

		//pares[i] = pares[2*i] + pares[2*i+1];
		//impares[i] = impares[2*i] + impares[2*i+1];
		st[i] = st[left(i)] + st[right(i)];
	}
}
int consulta( int e, int d, int i, int x, int y)
{
	if(y < e || d < x){
		return 0;
	}
	if( x <= e && y >= d){
		//return vetor[i];
		return st[i];
	}
	else
	{
		int meio = (d+e)/2;
		return consulta(e,meio,2*i,x,y) + consulta(meio+1,d,2*i+1,x,y);
	}
}
void atualizar(int* A, int i, int pos, int esq, int dir)
{
	if(esq > pos || dir < pos){
			return;
	}
	if(esq == dir && esq == pos){
		st[i] = A[esq];
	}
	else
	{
		int meio = (dir+esq)/2;
		atualizar(A,left(i),pos,esq,meio);
		atualizar(A,right(i),pos,meio+1,dir);
		st[i] = st[left(i)] + st[right(i)];
	}
}
int main()
{
	int n,m,i, esq, dir, op;
	int tam = 0;

	scanf("%d", &n);

	tam = 4*n;
	st = (int*)calloc(tam,sizeof(int));
	/*pares = (int*)calloc(tam,sizeof(int));
	impares = (int*)calloc(tam,sizeof(int));
	*/

	int v[n];
	int b[n];

	for(i=0;i<n;i++)
	{
		scanf("%d", &v[i]);
		if(Par(v[i])){
			b[i] = 1;
		}else{
			b[i] = 0;
		}

	}
	construir(b,1,0,n-1);

	/*Print(pares,1,tam);
	printf("\n");
	Print(impares,1,tam);*/
	scanf("%d", &m);
	for(i=0;i<m;i++)
	{
		scanf("%d%d%d", &op, &esq, &dir);
		
		if(op == 1){
			printf("%d\n", consulta(0,n-1,1,esq-1,dir-1));
		}
		else if(op == 2){
			printf("%d\n", (dir-esq + 1)-consulta(0,n-1,1,esq-1,dir-1));
		}
		else {

			v[esq-1] = dir;
			b[esq-1] = Par(v[esq-1]);
			atualizar(b,1,esq-1,0,n-1);
		}
	}
	return 0;
}
