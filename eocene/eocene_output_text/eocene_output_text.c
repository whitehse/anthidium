#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eocene.h>
#include "eocene_output_text.h"

#define init eocene_output_text_LTX_init
#define print eocene_output_text_LTX_print

int init(config_setting_t *config, struct ec_state *state) {
    return EC_OK;
}

int print (void *value, int vartype) {

    fprintf (stderr, "****%s****\n", value);
}
