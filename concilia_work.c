#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concilia_global.h"

#define TAMLIN 4096

char * separaCampos(char *strEntrada, char *delimitador, int numCampo)
{
    int i=0, contagem=0;
    char *strSaida=0;

    for(int i=0; i < strlen(strEntrada); i++)
    {
        if (strncmp (&strEntrada[i],delimitador,1) == 0)
        {
            contagem++;
        }
    }

    if(contagem < numCampo)
    {
        memset(strSaida,0,strlen(strSaida));
        return strSaida;
    }
    strSaida = strtok(strEntrada, delimitador);

    for(i=0;i < (numCampo);i++)
    {
        strSaida = strtok (NULL, delimitador);
    }
     
    return strSaida;
}

int separaChave(char entrada[])
{
    int i=0, j=0, k=0;
    char workin[4097];
  
    memset(&workin, 0, 4097);
  
    campos=0; posini=0; posfin=0;

    for(i=0;i<strlen(entrada);i++)
    {
        workin[j++] = entrada[i];  

        if(!strncmp(&entrada[i],".",1))
        {
            k++;
            campos = atoi(workin) - 1;
            memset(&workin, 0, 4097);
            j=0;
        }    
        if(!strncmp(&entrada[i],",",1))
        {
            k++;
            posini = atoi(workin) - 1;
            memset(&workin, 0, 4097);
            j=0;
        }    
    }
    if(k == 0) 
    { 
  	    campos = atoi(workin) - 1; 
  	    posini = 0; 
  	    tamanh = TAMLIN;
 	}
    if(k == 1) 
    { 
  	    posini = atoi(workin) - 1; 
  	    tamanh = TAMLIN; 
 	}
    if(k == 2) 
    { 
  	    tamanh = atoi(workin); 
    }
    return 0;
} 

int validaParam(int argc, const char **argv)
{
    char tudo[128];
    char *separados[5];

    int inda=0,indc=0,indb=0;

    contaKey = 0;	
    qtdIgnorar = 0;
	for (inda=0;inda<argc;inda++)
    {
        if (!strcmp(argv[inda],"-debug"))
        {
            flagDepurar = 1;
        }
        if (!strcmp(argv[inda],"-i"))
        {
            indc = inda+1;
            qtdIgnorar = atoi(argv[indc]);
        }
        if (!strcmp(argv[inda],"-t"))
        {
            indc = inda+1;
            memset(&separador,0,sizeof(separador));
            strncpy(separador,argv[indc],1);
        }
        if (!strcmp(argv[inda],"-k"))
        {
            indb=inda+1;
            memset(&separados,0,sizeof(separados));
            strcpy(tudo,argv[indb]);
            separaChave(tudo);
            posfin = (posini + tamanh) - 1;
            numCamKey[contaKey] = campos;
            posIniKey[contaKey] = posini;
            tamanhKey[contaKey] = tamanh;
            posFinKey[contaKey] = posfin;
            contaKey++;
        }
        if (!strcmp(argv[inda],"-stdin"))
        {
            flagEntrada = 1;
        }
    }
    return 0;
}

int montaChave(char *strEntrada)
{
    char strOriginal[4096];

    char *strSaida;

    int i=0;

    memset(strOriginal,0,sizeof(strOriginal));

    strcpy(strOriginal, strEntrada);

    memset(chavew,0,strlen(chavew));
    
    for(i=0;i<contaKey;i++)
    {
        strcpy(strEntrada, strOriginal);

        strSaida = separaCampos(strEntrada, separador, numCamKey[i]);

        strncat(chavew, &strSaida[posIniKey[i]], tamanhKey[i]); chavew[strlen(chavew)] = 0;
    }    
    return 0;
} 

