#include <stdio.h>
#include <string.h>

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

//Ex.4

#define MAX_NAME_LEN 50

int main(int argc, char* argv[])
{

	char nome[MAX_NAME_LEN];


	for	(int i=1;i<argc;i++)
	{
		sprintf(nome+strlen(nome),"%s",argv[i]);
		sprintf(nome+strlen(nome)," ");
	}

	printf("Hello %s !\n",nome);

	return 0;
}

