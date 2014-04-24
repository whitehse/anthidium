#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ltdl.h>
#include <eosimias.h>
#include <assert.h>
#include <libconfig.h>
#include <eosimias.h>
#include <eosimias_util.h>
#include "eonessa.h"

int eonessa_init (struct es_state *state, struct en_state **en_state_ref) {
    int errors = 0;
    struct en_state *en_state;
    config_setting_t *snmp_modules;
    int i;

    (*en_state_ref) = (struct en_state*)malloc(sizeof(struct en_state));
    en_state = *en_state_ref;
    memset(en_state, 0, sizeof (struct en_state));

    snmp_modules = config_lookup(state->cfg, "eonessa.snmp_modules");
    
    if (!snmp_modules) {
        fprintf(stderr, "configuration item 'eonessa.snmp_modules' could not be found.\n");
        free (en_state);
        return ES_BAD_CONFIG;
    }
    if (config_setting_is_array(snmp_modules) != CONFIG_TRUE) {
        fprintf(stderr, "configuration item 'eonessa.snmp_modules' is not an array.\n");
        free (en_state);
        return ES_BAD_CONFIG;
    }

    int number_of_snmp_modules = config_setting_length(snmp_modules);
    //memset(module_array, 0, sizeof(sub_eonessa_parse)*(MAX_NUM_OF_SUBMODULES+1));

    for (i=0; i<number_of_snmp_modules; i++) {
        const char *module = config_setting_get_string_elem(snmp_modules, i);
        errors = load_eosimias_module(module);
        if (errors) {
            fprintf(stderr, "Unable to load module %s: %s\n", module, eosimias_error_string(errors));
            free (en_state);
            return errors;
        }
    }

    //errors = load_eosimias_module(data_store_module);

    return ES_OK;
}

int eonessa_free (struct es_state *state, struct en_state *en_state) {

    free (en_state);

    return ES_OK;
}
