#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
//Exs.2-3
//int main2(void)
int main(void)
{
	printf("Hello !\n");
	return 0;
	//return 1;
}
*/

/*
//Ex.4 - carateres aleatorios entre hello e o nome

#define MAX_NAME_LEN 50

int main(int argc, char* argv[])
{

	char nome[MAX_NAME_LEN];

	int n=atoi(argv[1]);

	

	for	(int i=2;i<argc;i++)
	{
		sprintf(nome+strlen(nome),"%s",argv[i]);
		sprintf(nome+strlen(nome)," ");
	}

	for (int i=0;i<n;i++)
	{
		printf("Hello %s !\n",nome);
	}

	return 0;
}
*/

int main(int argc, char* argv[],char* envp[])
{
	//need a good way to calculate number of elements in envp

	for (int i=0;i<100;i++)
	{
		printf("%s\n",envp[i]);
	}
}
