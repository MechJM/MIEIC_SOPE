#include <stdio.h>

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
	printf("Indique o seu nome:\n");
	fgets(nome,MAX_NAME_LEN,stdin);

	while(getchar() != '\n');

	printf("Hello %s !",nome);

	return 0;
}

