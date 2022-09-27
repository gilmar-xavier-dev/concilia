#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <db.h>

#include "concilia_global.h"

#define TAMLIN 4096

char * separaCampos(char *strEntrada, char *delimitador, int numCampo);
int separaChave(char entrada[]);
int validaParam(int argc, char **argv);
int montaChave(char *strEntrada);
int criaBanco();
int acessaBanco();
int gravaBanco(char *chav, char *dado);
int leBanco(char *chav, char *dado);
int fechaBanco();

int main(int argc, char* argv[]) 
{

    int result=0, retorno=0,conta=0;

    char ARQUIV[128];
    char ARQSIM[128];
    char ARQNAO[128];

    FILE *f1,*f2, *f3;

/**********   Validação dos parametros de entrada   **********/ 

    result = validaParam(argc, argv);
    
    if(result != 0 || argc < 3)
    {
        printf("***************************************************************************************\n\n"); 
        printf("Erro na validação dos parametros de entrada, verifique-os !!!\n\n"); 
        printf("Use o formato: !!!\n\n"); 
        printf("./concilia ARQUIVO|-stdin -k X.Y,Z [-k X.Y,Z] -in|-out [-debug] [-ign 999] [-sep S] !!!\n\n"); 
        printf("Sendo:\n"); 
        printf("ARQUIVO|-stdin - Nome do arquivo de entrada, ou use -stdin para entrada manual ou via < \n"); 
        printf("-k X.Y,Z - informa a chave de conciliação (podem ser várias) X = Nro do campo (1 para registro fixo), Y = Posição inicial e Z = Tamanho\n"); 
        printf("-in|-out - in para arquivo a indexar e out para arquivo a conciliar - Irá procurar os registros do arquivo out no arquivo in\n"); 
        printf("-debug - OPCIONAL - Mostra na tela as operações realizadas\n"); 
        printf("-ign 000 - OPCIONAL - Ignora os primeiros 000 registros \n"); 
        printf("-sep S - OPCIONAL - Indica o caracter separador de campo, juntamente com o campo X do parâmetro -k\n\n"); 
        printf("Exemplo:\n"); 
        printf("./concilia arquivo1.txt -in  -k 1.11,18 -k 1.42,18 -k 1.76,6\n"); 
        printf("./concilia arquivo2.txt -out -k 1.10,18 -k 1.41,18 -k 1.75,6\n\n"); 
        printf("Os registros conciliados estarão em:\n"); 
        printf("arquivo2.txt-sim\n"); 
        printf("arquivo2.txt-nao\n"); 
        return -1;
    }
    if(flagOperacao != 1 && flagOperacao != 2)
    {
        printf("***************************************************************************************\n\n"); 
        printf("Erro na validação dos parametros de entrada, verifique-os !!!\n\n"); 
        printf("Operação com o arquivo deve ser informada, informe -in ou -out !!!\n\n"); 
        printf("Use o formato: \n"); 
        printf("./concilia ARQUIVO|-stdin -k X.Y,Z [-k X.Y,Z] -in|-out [-debug] [-ign 000] [-sep S] !!!\n"); 
        return -1;
    }

/**********   Abertura do arquivo de entrada   **********/ 

    if(flagEntrada == 1)
    {
       strcpy(ARQUIV,"ARQSEPCSV.csv");
    } 
    else
  	{
       strcpy(ARQUIV,argv[1]);
       f1 = fopen(ARQUIV,"r");
	     if (!f1)
	     {    
	         printf("ARQUIVO %s NÃO ENCONTRADO\n",ARQUIV);
	         return -1;
	     }
    }
    if(flagOperacao == 2)
    {
        strcpy(ARQSIM,ARQUIV); strcat(ARQSIM,"-sim");
        strcpy(ARQNAO,ARQUIV); strcat(ARQNAO,"-nao");
	    f2 = fopen(ARQSIM,"w");
	    if (!f2)
	    {    
	        printf("ERRO NA CRIAÇÃO DE %s\n",ARQSIM);
	        return(-1);
 	    }
	    f3 = fopen(ARQNAO,"w");
	    if (!f3)
	    {    
	        printf("ERRO NA CRIAÇÃO DE %s\n",ARQNAO);
	        return(-1);
 	    }
    }


/**********   Abertura do banco para indexacao   **********/ 

    if(flagOperacao == 1)
    {
        result = criaBanco();
    }
    else
    {
        result = acessaBanco();
    }

    if(result != 0)
    {
        printf("Erro na abertura do banco !!!\n"); 
        return -1;
    }

/**********   Leitura do arquivo de entrada   **********/ 

    conta = 0;
    retorno = 0;
	while (!retorno)
	{

        if(flagEntrada == 1)
        {
            if(fgets(lin, TAMLIN, stdin)==NULL)
            {
                retorno = 1;
                continue;
            }
        }
        else
        {
            if(fgets(lin, TAMLIN, f1)==NULL)
            {
                retorno = 1;
                continue;
            }
        }
        conta++;

/**********   Montagem das chaves de indexação   **********/ 

        result = montaChave(lin);

        if(result != 0)
        {
            printf("Erro na montagem da chave, verifique os parãmetros informados !!!\n"); 
            return -1;
        }

/**********   Gravacao dos dados no banco   **********/ 

        if(flagOperacao == 1)
        {
            result = gravaBanco(chavew, lin);
            if(result != 0)
            {
                printf("Erro na gravacao do banco, possível registro duplicado:\n%s\n",lin); 
                return -1;
            }
        }
        else
        {
            result = leBanco(chavew,lin);
            if(result == -2)
            {
                fputs(lin,f3);
            }
            else
            {
                if(result != 0)
                {
                    printf("Erro na leitura do banco !!!\n"); 
                    return -1;
                }
                fputs(lin,f2);
            }
        }

        if(flagDepurar == 1)
        {
            printf("Chave: <%s> Registro: <%s> Status: <%d>\n",chavew,lin,result);
        }

    }        

    result = fechaBanco();

    if(result != 0)
    {
        printf("Erro no fechamento do banco !!!\n"); 
        return -1;
    }
    if(flagEntrada == 0)
    {
        fclose(f1);
    }    
    if(flagOperacao == 2)
    {
        fclose(f2);
        fclose(f3);
    }

    return 0;
}
