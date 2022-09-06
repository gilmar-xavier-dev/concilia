#include <stdio.h>
#include <string.h>

#define TAMLIN 4096

int campos, tamanh, posini, posfin;

char *strSep(char **stringp, const char *delim) 
{
    char *s;
    const char *spanp;
    int c, sc;
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

verificaParam(int argc, char **argv, int *depurar, int *entrada)
{

    printf("<%d><%s>\n" ,argc, argv[1]);

    int inda=0,indb=0,indc=0,qtdign=0,contak=0;
    char separa[2];
    char *separados[5];
    char tudo[128];
    int numcamk[24];
    int posinik[24];
    int tamanhk[24];
    int posfink[24];

    strncpy(separa,"\n",1);
    contak = 0;	
    qtdign = 0;
	for (inda=0;inda<argc;inda++)
  {
     if (!strcmp(argv[inda],"-debug"))
     {
       *depurar = 1;
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
     if (!strcmp(argv[inda],"-stdin"))
     {
       *entrada = 1;
     }
  }
  printf("<Dep: <%d> ENT: <%d>\n",&depurar,&entrada);
 return 0;
}