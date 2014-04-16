#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eosimias.h>
#include <eocene.h>
#include "eocene_ethernet.h"
#include "eocene_stp.h"

#define init eocene_stp_LTX_init
#define parse eocene_stp_LTX_parse

struct es_state *state;

eocene_stp_listener *stp_listeners[EC_STP_MAX_LISTENERS];
int number_of_stp_listeners = 0;

int register_listener(void *callback) {
    stp_listeners[number_of_stp_listeners] = callback;
    number_of_stp_listeners += 1;
}

int my_eocene_ethernet_listener(struct ec_ethernet *frame) {
    struct ec_stp *stp;
    stp = (struct ec_stp*)malloc(sizeof(struct ec_stp));

    if ((frame->payload_ethertype == EC_ETH_ETHER_802_DOT_1_STP)
         || (frame->contents & EC_ETH_CONTAINS_SNAP_HEADER)
            & (frame->llc_source_sap == EC_ETH_SAP_IEEE_802_DOT_1_STP)) {
        fprintf (stderr, "  Frame is an 802.1d STP packet.\n");
    } else {
        fprintf (stderr, "  Frame is not an 802.1d STP packet.\n");
        return ES_OK;
    }

    if (frame->payload_length < 35) {
        fprintf (stderr, "STP payload length is too small (%d - should be 35).\n", frame->payload_length);
    }

    char* buf = frame->payload_pointer;
    //int offset = 0;
    stp->protocol_id = ntohs(*(uint16_t *)(buf));
    stp->version_id = *(uint8_t *)(buf+2);
    stp->bpdu_type = *(uint8_t *)(buf+3);
    stp->flags = *(uint8_t *)(buf+4);
    stp->root_bridge_priority = (*(uint8_t *)(buf+5) >> 4) * 4096;
    fprintf (stderr, "  root bridge priority is %d.\n", stp->root_bridge_priority);
//    state->printer("The MFin root bridge priority is ...\n", 0);
    stp->root_bridge_system_id_extension = ntohs((*(uint16_t *)(buf+5))) & 0x0fff;
    memcpy (stp->root_bridge_mac, buf+7, 6);
    stp->root_path_cost = ntohl(*(uint32_t *)(buf+13));
    stp->bridge_priority = (*(uint8_t *)(buf+17) >> 4) * 4096;
    stp->bridge_system_id_extension = ntohs((*(uint16_t *)(buf+17))) & 0x0fff;
    memcpy (stp->bridge_mac, buf+19, 6);
    stp->port_id = ntohs(*(uint16_t *)(buf+25));
    stp->message_age = ntohs(*(uint16_t *)(buf+27));
    stp->max_age = ntohs(*(uint16_t *)(buf+29));
    stp->hello_time = ntohs(*(uint16_t *)(buf+31));
    stp->forward_delay = ntohs(*(uint16_t *)(buf+33));
    fprintf (stderr, "  forward delay is %d.\n", stp->forward_delay);

    // Further processing
    int i;
    for (i=0; i<number_of_stp_listeners; i++) {
        eocene_stp_listener listener_cb = stp_listeners[i];
        listener_cb (stp);
    }

}

int init(config_setting_t *config, struct es_state *_state) {
    eocene_ethernet_register_listener register_function;
    int result;
    state = _state;
    result = find_eocene_symbol ("eocene_ethernet", "register_listener", &(register_function));
    (*register_function) (my_eocene_ethernet_listener);

    char *module_path = NULL;
    config_lookup_string(state->cfg, "module_path", &module_path);
    fprintf (stderr, "module path (in the config) is %s.\n", module_path);

    return ES_OK;
}
