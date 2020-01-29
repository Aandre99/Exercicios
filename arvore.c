#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
	char letra[] = "aBCDL";
	char * aux = letra;

	printf("%c", aux[0]);
	printf("%s", (aux+1));
	return 0;
}