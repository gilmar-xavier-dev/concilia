#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "concilia_global.h"

void doSomething();
void doSomething2();
char * separaCampos(char *strEntrada, char *delimitador, int numCampo);
int validaParam(int argc, const char **argv);
int montaChave(char *strEntrada);

int main(int argc, char* argv[]) 
{

    int result=0;

    char strEntrada[] = "teste;DESSA;coisa;TENTANDO;saber;COMO;funciona";
        

/**********   Validação dos parametros de entrada   **********/ 

    result = validaParam(argc, argv);
    
    if(result != 0)
    {
        printf("Erro na validação dos parametros de entrada, verifique-os !!!\n"); 
        return -1;
    }

/**********   Montagem das chaves de indexação   **********/ 

    result = montaChave(strEntrada);

    if(result != 0)
    {
        printf("Erro na montagem da chave, verifique os parãmetros informados !!!\n"); 
        return -1;
    }

    printf("<%s>\n",chavew);

    return 0;
}
