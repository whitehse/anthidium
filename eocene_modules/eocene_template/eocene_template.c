#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eonessa.h>
#include <eocene.h>
#include "eocene_template.h"

int init(config_setting_t *config, struct ec_state *_state) {
    return EC_OK;
}

int parse(const char* buf, unsigned n, int flags, struct eonessa *en) {
    int i;
    int offset=0;
}
