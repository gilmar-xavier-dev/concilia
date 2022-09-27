#include <stdio.h>
#include <string.h>
#include <gdbm.h>
#include "concilia_global.h"

GDBM_FILE concilia_db;
datum key, data;
#define datum_set(um, buf) { um.dptr = buf; um.dsize = strlen(buf); }

#define DATABASE "indexado.db"
#define TAMLIN 4096

int criaBanco();
int acessaBanco();
int gravaBanco(char *chav, char *dado);
int leBanco(char *chav, char *dado);
int fechaBanco();

int criaBanco()
{
   int dbflags = GDBM_NEWDB;
    concilia_db = gdbm_open(DATABASE, 0, dbflags, 0664, 0);
    if(!concilia_db)
    {
        fprintf (stderr, "Erro ao abrir o banco %s \n", DATABASE);
        return -1;
    }
    return 0;
}

int acessaBanco()
{

   int dbflags = GDBM_READER;
    concilia_db = gdbm_open(DATABASE, 0, dbflags, 0664, 0);
    if(!concilia_db)
    {
        fprintf (stderr, "Erro ao abrir o banco %s \n", DATABASE);
        return -1;
    }
    return 0;
}

int gravaBanco(char *chav, char *dado)
{
    datum_set(key, chav);
    datum_set(data, dado);

    key.dsize = strlen(chav) + 1;

    if(gdbm_store(concilia_db,key,data,GDBM_INSERT))
    {
        return -2;
    }
    return 0;
}

int leBanco(char *chav, char *dado)
{
   datum_set(key, chav);

    key.dsize = strlen(chav) + 1;

    data = gdbm_fetch(concilia_db,key);
    if (data.dsize <= 0)
    {
        return -2;
    }
    else
    {
        strncpy(dado, data.dptr, data.dsize);
    }
    return 0;
}

int fechaBanco()
{
    gdbm_close (concilia_db);
    return 0;
}
