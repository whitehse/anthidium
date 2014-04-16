#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eosimias.h>
#include <eocene.h>
#include "eocene_ethernet.h"
#include "eocene_stp.h"
#include "eocene_bridge_network.h"

#define init eocene_bridge_network_LTX_init
#define parse eocene_bridge_network_LTX_parse

struct ec_state *state;

int my_eocene_stp_listener(struct ec_stp *stp) {
    struct ec_bridge_network *bridge_network;
    bridge_network = (struct ec_bridge_network*)malloc(sizeof(struct ec_bridge_network));
    fprintf (stderr, "eocene_bridge_network's stp listener was called.\n");
    return ES_OK;
}

int init(config_setting_t *config, struct ec_state *_state) {
    eocene_stp_register_listener register_function;
    int result;
    state = _state;
    result = find_eocene_symbol ("eocene_stp", "register_listener", &(register_function));
    (*register_function) (my_eocene_stp_listener);

    return ES_OK;
}
