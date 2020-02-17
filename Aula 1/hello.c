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

	char nome[MAX_NAME_LEN] = "";

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

/*
//Ex.5 b)

int main(int argc, char* argv[],char* envp[])
{
	char word_user[5]="USER=";

	for (char **it=envp;*it!=0;it++)
	{
		char *current=*it;
		if (strncmp(word_user,current,5)==0) 
		{
			char username[50];
			strncpy(username,current+5,50);
			printf("Hello %s !\n",username);
		}	
	}

	return 0;
}
*/


//Ex.5 c) e d) - e suposto escaparmos os espaços?
int main(int argc, char* argv[],char* envp[])
{
	char username[50];

	//c)
	//char word_user[4]="USER";

	//d)
	char word_user_name[9]="USER_NAME";

	//c)
	//strcpy(username,getenv(word_user));

	//d)
	strcpy(username,getenv(word_user_name));

	printf("Hello %s !\n",username);

	return 0;
}

