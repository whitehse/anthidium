#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eosimias.h>
#include <eonessa.h>
#include "eonessa_snmp_snmpv2_mib.h"

int init(struct es_state *state, struct en_state *en_state) {
    fprintf (stderr, "eonessa's snmpv2_mib init was entered.\n");
    return ES_OK;
}
