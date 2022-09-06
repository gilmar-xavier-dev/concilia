#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <db.h>

#define DATABASE "indexado.db"

#define TAMLIN 4096

int campos, tamanh, posini, posfin;

char *
strSep(stringp, delim)
        register char **stringp;
        register const char *delim;
{
        register char *s;
        register const char *spanp;
        register int c, sc;
        char *tok;

        if ((s = *stringp) == NULL)
                return (NULL);
        for (tok = s;;) {
                c = *s++;
                spanp = delim;
                do {
                        if ((sc = *spanp++) == c) {
                                if (c == 0)
                                        s = NULL;
                                else
                                        s[-1] = 0;
                                *stringp = s;
                                return (tok);
                        }
                } while (sc != 0);
        }
} 


int separaChave(char entrada[])
{
  int i=0, j=0, k=0;
  char workin[TAMLIN];
  
  memset(&workin, 0, TAMLIN);
  
  campos=0; posini=0; posfin=0;

  for(i=0;i<strlen(entrada);i++)
  {
    workin[j++] = entrada[i];  

    if(!strncmp(&entrada[i],".",1))
    {
       k++;
       campos = atoi(workin) - 1;
       memset(&workin, 0, TAMLIN);
       j=0;
    }    
    if(!strncmp(&entrada[i],",",1))
    {
    	 k++;
       posini = atoi(workin) - 1;
       memset(&workin, 0, TAMLIN);
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

int main(int argc, char *argv[])
{
    if(argc < 4)
	  {
	      printf("FORMATO INVÁLIDO, DEVE SER: sepcsv arquivo [-debug] -t <separador> -k <campo.inicio,tamanho> [-i qtde_ignorar] [-dados] [-stdin] [-naooff]\n");
	  	  return(-1);
    }

    char ARQUIV[128];
    char ARQSIM[128];
    char ARQNAO[128];

	  FILE *f1,*f2,*f3;
    int tamlin = 4096;
    int TAMBUS = 0;

    char regis[TAMLIN];
	  printf("\nSEPARANDO REGISTROS DO ARQUIVO %s\n", argv[1]); 
	  char lin[TAMLIN];
	  char linha[TAMLIN];
	  char gravacao[TAMLIN];
	  char linhas[TAMLIN];
	  char registro[TAMLIN];
	  char cnl[6];
	  char chavew[TAMLIN];
	  char dadosw[TAMLIN];
	  int x=0;
	  int i=0,lid=0;
	  int j=0;
	  int k=0;
	  int conta=0;

	  int inda=0,indb=0,indc=0,indk=0,qtdign=0,depurar=0,contak=0,mostrar=0,entrada=0,semnao=0,retorno=0,valida=0;
    char *separados[256];
    int numcamk[24];
    int posinik[24];
    int tamanhk[24];
    int posfink[24];
    char tudo[128];
    char separa[2];
	
    printf("ABRINDO BANCO...\n");

    char * pch;
    char *ponteiro;

    DB *dbp = NULL;
    char tecla[1], *chavep, *dadosp;
    DBT chave, dados;
    int ret, t_ret;

    ret = db_create(&dbp, NULL, 0);
    if (ret != 0) {
        fprintf(stderr, "db_create: %s\n", db_strerror(ret));
        goto err;
    }

    ret = dbp->open(dbp, NULL, DATABASE, NULL, DB_BTREE,
            DB_RDONLY, 0664);
    if (ret != 0) {
        dbp->err(dbp, ret, "%s", DATABASE);
        goto err;
    }

    printf("Verificando Parâmetros...\n");

    contak = 0;	
    qtdign = 0;
  	for (inda=0;inda<argc;inda++)
    {
       if (!strcmp(argv[inda],"-debug"))
       {
         depurar = 1;
       }
       if (!strcmp(argv[inda],"-dados"))
       {
         mostrar = 1;
       }
       if (!strcmp(argv[inda],"-stdin"))
       {
         entrada = 1;
       }
       if (!strcmp(argv[inda],"-naooff"))
       {  
         semnao = 1;
       }
       if (!strcmp(argv[inda],"-i"))
       {
         indc = inda+1;
         qtdign = atoi(argv[indc]);
       }
     if (!strcmp(argv[inda],"-t"))
     {
       indc = inda+1;
       memset(&separa,0,sizeof(separa));
       strncpy(separa,argv[indc],1);
     }
     if (!strcmp(argv[inda],"-k"))
     {
       indb=inda+1;
       memset(&separados,0,sizeof(separados));
       strcpy(tudo,argv[indb]);
       separaChave(tudo);
       posfin = posfin + tamanh;
       numcamk[contak] = campos;
       posinik[contak] = posini;
       tamanhk[contak] = tamanh;
       posfink[contak] = posfin;
       contak++;
     }
    }

    printf("Abrindo Arquivos...\n");

    if(entrada == 1)
    {
       strcpy(ARQUIV,"ARQSEPCSV.csv");
    } 
    else
  	{
       strcpy(ARQUIV,argv[1]);
    }
    strcpy(ARQSIM,ARQUIV); strcat(ARQSIM,"-sim");
    strcpy(ARQNAO,ARQUIV); strcat(ARQNAO,"-nao");
    
    if(entrada == 0)
    {
       f1 = fopen(ARQUIV,"r");
	     if (!f1)
	     {    
	         printf("ARQUIVO %s NÃO ENCONTRADO\n",ARQUIV);
	         return(-1);
	     }
    }
	  f2 = fopen(ARQSIM,"w");
	  if (!f2)
	  {    
	      printf("ERRO NA CRIAÇÃO DE %s\n",ARQSIM);
	      return(-1);
 	  }
    if(semnao == 0)
    	{
	     f3 = fopen(ARQNAO,"w");
	     if (!f3)
	     {    
	         printf("ERRO NA CRIAÇÃO DE %s\n",ARQNAO);
	        return(-1);
	     }
	  }

    printf("Lendo Arquivo...\n");

    conta = 0;
    retorno = 0;
	  while (!retorno)
	  {

        if(entrada == 1)
        {
           if(fgets(lin, TAMLIN, stdin)==NULL)
           {
        		   retorno = 1;
           }
        }
        else
        {
           if(fgets(lin, TAMLIN, f1)==NULL)
           {
        		   retorno = 1;
           }
        }
        valida = 0;
		    conta++;
        if (conta > qtdign) 
        {
           tamlin=(strlen(lin))-1;
           lid++;
           strncpy(registro, &lin[  0], tamlin);  registro[tamlin] = 0;
           
          ponteiro = strdup (registro);

          pch = strSep (&ponteiro,separa);

          i=0;
          while( pch != NULL ) 
          {
             separados[i] = pch;
             pch = strSep (&ponteiro,separa);
             i++;
          }

          memset(&chave, 0, sizeof(chave));
          memset(&dados, 0, sizeof(dados));
  
          chavew[0]=0;

          memset(chavew,0,strlen(chavew));
          posfin=0;
          for (indk=0;indk<contak;indk++)
          {
               campos = numcamk[indk];            
               if (campos > i)
               {
                 valida=1;
                 break;
               }
               posini = posinik[indk];
               tamanh = tamanhk[indk]; 
               posfin = posfink[indk];
               strncat(chavew, &separados[campos][posini], tamanh); chavew[strlen(chavew)] = 0;
          }
           if (valida == 1)
           {
             continue;
           }
           if (depurar == 1)
           {
             printf("Chave:%s\n",chavew);
           }
           chavep = chavew;
   
           dadosw[0]=0;
           dadosp = dadosw;
   
           chave.data = chavep;
           chave.size = strlen(chavep);
   
           dados.data = dadosp;
           dados.size = strlen(dadosp);
           
           memset(dadosp,0,sizeof(dadosp));
           memset(dados.data,0,dados.size);
           dados.size = 0;
           
           if ((ret = dbp->get(dbp, NULL, &chave, &dados, 0)) != 0) 
           {
           	  if (ret == DB_NOTFOUND) 
           	  {
           	  	  if(semnao == 0)
           	  	  {
                     fputs(lin,f3);
                  }
                  k++;
           	  }
           	  else
           	  {
   	             fprintf(stderr, "Erro na gravação: %s\n", db_strerror(ret));
   	             return (1);
   	          }
           }
           else
           {
               if(mostrar == 1 ) 
               {
                   memset(dadosp,0,sizeof(dadosp));
                   dadosp = dados.data;
                   memset(dadosw,0,sizeof(dadosw));
                   memset(linha,0,sizeof(linha));
                   strncpy(dadosw,dadosp,dados.size);
                   strncpy(linha,lin,strlen(lin)-1);
                   sprintf(gravacao,"%s;%s\n",dadosw,linha);
                   fputs(gravacao,f2);
                   j++;
               }
               else
               {
                   fputs(lin,f2);
                   j++;
 
               }
           }
        }
    }
    if(entrada == 0)
    {
       fclose(f1);
    }    
    fclose(f2);
    
    if(semnao == 0)
    {
       fclose(f3);
    }
    printf("Lidos.......: %d\n",lid);
    printf("Encontrados.: %d\n",j);
    printf("Não Encontr.: %d\n",k);
    printf("FINAL DE PROCESSAMENTO !!!\n");
    t_ret = dbp->close(dbp, 0);
    return(0);

err:
    if (dbp) {
        t_ret = dbp->close(dbp, 0);
        if (t_ret != 0 && ret == 0)
            ret = t_ret;
    }

    exit(ret);
}
