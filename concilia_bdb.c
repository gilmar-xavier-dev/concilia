#include <db.h>

#define DATABASE "indexado.db"
#define TAMLIN 4096

int criacaoDB()
{
    DB *dbp = NULL;
    int ret;

    ret = db_create(&dbp, NULL, 0);
    if (ret != 0) {
        fprintf(stderr, "db_create: %s\n", db_strerror(ret));
        return 1;
    }

    ret = dbp->open(dbp, NULL, DATABASE, NULL, DB_BTREE,
            DB_CREATE | DB_TRUNCATE, 0664);
    if (ret != 0) {
        dbp->err(dbp, ret, "%s", DATABASE);
        return 2;
    }
  return 0;
} 

int aberturaDB()
{
    DB *dbp = NULL;
    int ret;

    ret = db_create(&dbp, NULL, 0);
    if (ret != 0) {
        fprintf(stderr, "db_create: %s\n", db_strerror(ret));
        return 1;
    }

    ret = dbp->open(dbp, NULL, DATABASE, NULL, DB_BTREE,
            DB_RDONLY, 0664);
    if (ret != 0) {
        dbp->err(dbp, ret, "%s", DATABASE);
        return 2;
    }

  return 0;
} 

int gravacaoDB(char chave[], char dados[])
{
    DB *dbp = NULL;
    int ret;

    ret = db_create(&dbp, NULL, 0);
    if (ret != 0) {
        fprintf(stderr, "db_create: %s\n", db_strerror(ret));
        return 1;
    }

    ret = dbp->open(dbp, NULL, DATABASE, NULL, DB_BTREE,
            DB_RDONLY, 0664);
    if (ret != 0) {
        dbp->err(dbp, ret, "%s", DATABASE);
        return 2;
    }

  return 0;
} 

char leituraDB(char chave[])
{
    DB *dbp = NULL;

    return NULL;
} 

int bdb(int abertura)
{

    char chave[TAMLIN];
    char dados[TAMLIN];
    
    switch (abertura)
    {
        case 1:
          criacaoDB();
        break;

        case 2:
          aberturaDB();
        break;

        case 3:
            gravacaoDB(chave, dados);
        break;

        case 4:
            leituraDB(chave);
        break;

        default: 
            return 1;
    }
    return 0;
}
