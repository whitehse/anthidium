#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eocene.h>
#include "eocene_ethernet.h"
#include "eocene_ipv4.h"

int my_eocene_ethernet_listener(struct ec_ethernet *frame, const char* buf, unsigned buf_len) {
    fprintf (stderr, "ipv4's ethernet listener function was entered.\n");
}

int init(config_setting_t *config, struct ec_state *_state) {
    fprintf (stderr, "ipv4's init function was called.\n");
    return EC_OK;
//    eocene_ethernet_register_listener register_function;
//    int result;
//    result = find_eocene_symbol ("eocene_ethernet", "register_listener", &(register_function));
//    (*register_function) (my_eocene_ethernet_listener);
//    return EC_OK;
}
