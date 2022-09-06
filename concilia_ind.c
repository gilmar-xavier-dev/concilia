#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int entrada=0,depurar=0;

int main(int argc, char *argv[])
{

#define CRIAR 1
#define ABRIR 2
#define GRAVA 3
#define LEITU 4

	int status=0;
    if(argc < 4)
	  {
	      printf("FORMATO INVÁLIDO, DEVE SER: concilia arquivo [-debug] -t <separador> -k <campo.inicio,tamanho> [-i qtde_ignorar] [-stdin]\n");
	  	  return(-1);
    }
    if(criacaoDB())
    {
	      printf("Erro na criação\n");
	  	  return(-1);
    }

    printf("<%d> <%s> Dep: <%d> ENT: <%d>\n",argc,argv[1],depurar,entrada);

    if(verificaParam(argc, argv, &depurar, &entrada))
    {
	      printf("Erro parametros\n");
	  	  return(-1);
    }

    printf("Dep: %d ENT: %d\n",depurar,entrada);

    return 0;
}
