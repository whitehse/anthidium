#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <db.h>
#include <eosimias.h>
#include "eosimias_bdb.h"

#define init eosimias_bdb_LTX_init

int init(struct es_state *state) {
    fprintf (stderr, "eosimias's bdb init was entered.\n");
    return ES_OK;
}

int open_table (void **db, char *table) {
    int ret;
    DB *dbp = NULL;

    if ((ret = db_create(&dbp, NULL, 0)) != 0) {
        fprintf(stderr, "db_create: %s\n", db_strerror(ret));
        exit (1);
    }

    if ((ret = dbp->open(
      dbp, NULL, table, NULL, DB_BTREE, DB_CREATE, 0)) != 0) {
        dbp->err(dbp, ret, "%s", table);
        exit (1);
    }

    *db = dbp;

    return ES_OK;
}

int put (void **db, void *key, int key_len, void *value, int value_len) {
    int ret;
    DBT db_key, db_data;

    DB *dbp = *db;


    memset(&db_key, 0, sizeof(db_key));
    memset(&db_data, 0, sizeof(db_data));
    db_key.data = key;
    db_key.size = key_len;
    db_data.data = value;
    db_data.size = value_len;


    if ((ret = dbp->put(dbp, NULL, &db_key, &db_data, 0)) == 0)
        printf("db: %s: key stored.\n", (char *)db_key.data);
    else {
        dbp->err(dbp, ret, "DB->put");
        exit(1);
    }

    return ES_OK;
}

int get (void **db, void *key, int key_len, void *value, int value_len) {
    int ret;
    DB *dbp = *db;
    DBT db_key, db_data;

    memset(&db_key, 0, sizeof(db_key));
    memset(&db_data, 0, sizeof(db_data));

    db_key.data = key;
    db_key.size = key_len;

    dbp->get(dbp, NULL, &db_key, &db_data, 0);

    value = db_data.data;
    value_len = db_data.size;

    return ES_OK;
}

int del (void **db, void *key, int key_len, void *value, int value_len) {
    int ret;
    DB *dbp = *db;
    DBT db_key;

    memset(&db_key, 0, sizeof(db_key));
    db_key.data = key;
    db_key.size = key_len;

    if (ret = dbp->del(dbp, NULL, key, 0)) {
        dbp->err(dbp, ret, "DB->del");
        exit(1);
    }
}

int close_table (void **db) {
    DB *dbp = *db;
    if (dbp != NULL)
        dbp->close(dbp, 0);
}
