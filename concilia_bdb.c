#include <stdio.h>
#include <string.h>
#include <db.h>
#include "concilia_global.h"

DB *concilia_db;

#define DATABASE "indexado.db"
#define TAMLIN 4096

int criaBanco();
int acessaBanco();
int gravaBanco(char *chav, char *dado);
int leBanco(char *chav, char *dado);
int fechaBanco();

int criaBanco()
{

    int retval=0;

    retval = db_create(&concilia_db, NULL, 0);
    if(retval!=0)
    {
        printf("db_create: %s\n", db_strerror(retval));
        return -1;
    }
    int dbflags = DB_CREATE | DB_TRUNCATE;
    retval = concilia_db->open(concilia_db, NULL, DATABASE, NULL, DB_BTREE, dbflags, 0664);
    if(retval!=0)
    {
        concilia_db->err(concilia_db, retval, "erro abrindo banco");
        return -1;
    }
    return 0;
}

int acessaBanco()
{

    int retval=0;

    retval = db_create(&concilia_db, NULL, 0); 
    if(retval!=0)
    {
        printf("db_create: %s\n", db_strerror(retval));
        return -1;
    }
    int dbflags = DB_RDONLY;
    retval = concilia_db->open(concilia_db, NULL, DATABASE, NULL, DB_BTREE, dbflags, 0664);
    if(retval!=0)
    {
        concilia_db->err(concilia_db, retval, "erro acessando banco");
        return -1;
    }
    return 0;
}

int gravaBanco(char *chav, char *dado)
{
    int retval = 0;

    DBT key;
    DBT value;

    char *pchav;
    char *pdado;

    memset(&key,0,sizeof(key));
    memset(&value,0,sizeof(value));

    memset(&pchav,0,sizeof(pchav));
    memset(&pdado,0,sizeof(pdado));

    pchav = chav;
    pdado = dado;

    key.data = pchav;
    key.size = strlen(pchav);

    value.data = pdado;
    value.size = strlen(pdado);

    retval = concilia_db->put(concilia_db, NULL,  &key,   &value, DB_NOOVERWRITE);
    if(retval != 0)
    {
        if (retval == DB_KEYEXIST)
        {
            return -2;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return 0;
    }
}

int leBanco(char *chav, char *dado)
{
    int retval = 0;

    DBT key;
    DBT value;

    char *pchav;
    char *pdado;

    memset(&key,0,sizeof(key));
    memset(&value,0,sizeof(value));

    memset(&pchav,0,sizeof(pchav));
    memset(&pdado,0,sizeof(pdado));

    pchav = chav;
    pdado = dado;

    key.data = pchav;
    key.size = strlen(pchav);

    value.data = pdado;
    value.size = strlen(pdado);

    retval = concilia_db->get(concilia_db, NULL,  &key,   &value, 0);
    if(retval != 0)
    {
        if (retval == DB_NOTFOUND)
        {
            return -2;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        pdado = value.data;
        strncpy(dado, pdado, value.size);
    }
    return 0;
}

int fechaBanco()
{
    int retval = 0;
    retval = concilia_db->close(concilia_db, 0);
    return retval;
}
