#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eosimias.h>
#include <eocene.h>
#include "eocene_sockets.h"

#define init eocene_sockets_LTX_init
#define parse eocene_sockets_LTX_parse

struct es_state *state;

void *socket_table_ref;
void **socket_table_ref_ref;

int init(config_setting_t *config, struct es_state *_state) {
    
    state = _state;

    socket_table_ref = "A";
    socket_table_ref_ref = &socket_table_ref;

    (state->open_table)(socket_table_ref_ref, "sockets.db");
    char *val = "stuff";
//    char **val_ref;
//    *val_ref = val;
    int val_len = 4;
//    int *val_len_ref;
//    *val_len_ref = val_len;
//    (state->put)(socket_table_ref_ref, "test", 4, &val, &val_len);

    return ES_OK;
}
