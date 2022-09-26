#include <stdio.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include "concilia_global.h"

redisContext *c;
redisReply *reply;

#define TAMLIN 4096

int criaBanco();
int acessaBanco();
int gravaBanco(char *chav, char *dado);
int leBanco(char *chav, char *dado);
int fechaBanco();

int criaBanco()
{
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds

    c = redisConnectWithTimeout("127.0.0.1", 6379, timeout);  /* localhost, porta, 1,5 seg timeout */
	if (c == NULL || c->err) 
	{
	    if (c) 
		{
		    redisFree(c);
		} 
        return -1;
	}
  	reply = redisCommand(c,"FLUSHALL");
	freeReplyObject(reply);

    return 0;
}

int acessaBanco()
{
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds

    c = redisConnectWithTimeout("127.0.0.1", 6379, timeout);  /* localhost, porta padrão, 1,5 seg timeout */
	if (c == NULL || c->err) 
	{
	    if (c) 
		{
		    redisFree(c);
		} 
        return -1;
	}
    return 0;
}

int gravaBanco(char *chav, char *dado)
{

    char *pchav;
    char *pdado;

    memset(&pchav,0,sizeof(pchav));
    memset(&pdado,0,sizeof(pdado));

    pchav = chav;
    pdado = dado;

    reply = redisCommand(c,"SET %s %s", pchav, pdado);
    freeReplyObject(reply);
    
    return 0;

}

int leBanco(char *chav, char *dado)
{

    char *pchav;
    char *pdado;

    memset(&pchav,0,sizeof(pchav));
    memset(&pdado,0,sizeof(pdado));

    pchav = chav;
    pdado = dado;

    reply = redisCommand(c,"GET %s",pchav);
    freeReplyObject(reply);

    if(reply->str == NULL)
    {
        return -2;
    }
    else
    {
        pdado = reply->str;
        strncpy(dado, pdado, strlen(pdado));
        return 0;
    }
}

int fechaBanco()
{
    int retval = 0;
	redisFree(c);
    return retval;
}
