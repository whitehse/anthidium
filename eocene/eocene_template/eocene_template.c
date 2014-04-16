#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eosimias.h>
#include <eocene.h>
#include "eocene_template.h"

#define init eocene_template_LTX_init
#define parse eocene_template_LTX_parse

int init(config_setting_t *config, struct es_state *_state) {
    return ES_OK;
}
