#include <stdio.h>
#include <stdlib.h>

void mostrarBitmap(int l, int c, int** B)
{
	int i, j;

	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			printf("%d ", B[i][j]);
		}
		printf("\n");
	}

	for(i=0;i<l;i++)
	{
		free(B[i]);
	}
	free(B);
	B = NULL;
}
int main(){

	int i,j,l,c,n;
	int** bitmap = NULL;

	int qtd_linhas, qtd_colunas;

	scanf("%d", &n);

	for(i=0;i<n;i++)
	{
		scanf("%d%d", &qtd_linhas,&qtd_colunas);

		bitmap = (int**)calloc(qtd_linhas,sizeof(int*));

		for(l=0;l<qtd_linhas;l++)
		{
			bitmap[l] = (int*)calloc(qtd_colunas,sizeof(int));
			
			for(c=0;c<qtd_colunas;c++)
			{
				scanf("%d", &bitmap[l][c]);
			}
		}
		printf("Li a %d matrix\n", i+1);
		mostrarBitmap(qtd_linhas,qtd_colunas,bitmap);

	}
	return 0;
}