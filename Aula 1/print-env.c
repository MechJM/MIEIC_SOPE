#include<stdio.h>

//Ex.5 a)
int main(int argc, char* argv[],char* envp[])
{
	for (char **it=envp;*it!=0;it++)
	{
		char *current=*it;
		printf("%s\n",current);
	}
}