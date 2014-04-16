#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eosimias.h>
#include <eocene.h>
#include "eocene_output_text.h"

#define init eocene_output_text_LTX_init
#define print eocene_output_text_LTX_print

int init(config_setting_t *config, struct es_state *state) {
    return ES_OK;
}

int print (void *value, int vartype) {

    fprintf (stderr, "****%s****\n", value);
}
