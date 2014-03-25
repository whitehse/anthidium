#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eonessa.h>
#include <eocene.h>
#include "eocene_sockets.h"

struct ec_state *state;

void *socket_table_ref;
void **socket_table_ref_ref;

int init(config_setting_t *config, struct ec_state *_state) {
    
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

    return EC_OK;
}

int parse(struct eonessa_clump *clump) {
    fprintf(stderr, "parse (within eocene_sockets) was called.\n");
}
