#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

int main(void)
{
    while (1)
    {
        int num1,num2;
        printf("Indique dois numeros: ");
        scanf("%d %d",&num1,&num2);

        FILE* reqPtr = fopen("/tmp/fifo_req","w");
        if (reqPtr == NULL) break;
        fprintf(reqPtr,"%d %d",num1,num2);
        fclose(reqPtr);

        FILE* ansPtr = fopen("/tmp/fifo_ans","r");
        if (ansPtr == NULL) break;
        int sum,diff,prod;
        float div;
        fscanf(ansPtr,"%d\n%d\n%d\n%f",&sum,&diff,&prod,&div);
        fclose(ansPtr);
        printf("Soma: %d\n",sum);
        printf("Diferenca: %d\n",diff);
        printf("Produto: %d\n",prod);
        if (div == -1) printf("A divisao nao e valida.\n");
        else printf("Razao: %f\n",div);
    }
    return 0;
}