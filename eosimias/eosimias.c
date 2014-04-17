#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ltdl.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <libconfig.h>
#include <assert.h>
#include "eosimias.h"
#include "eosimias_util.h"

int eosimias_init (struct es_state *state, struct config_t *cfg) {
    int errors = 0;
    char *module_path = NULL; /* libconfig will manage memory for this */
    char *path = NULL;
    char *data_store_module = NULL;
    char *event_module = NULL;

    assert (cfg);

    errors = lt_dlinit ();
    if (errors)
        return ES_CANT_DLINIT;

    state = (struct es_state*)malloc(sizeof(struct es_state));    
    memset(state, 0, sizeof (struct es_state));

    state->cfg = cfg;

    path = getenv (EOSIMIAS_PLUGIN_PATH);

    if (path == NULL) {
        if (config_lookup_string(state->cfg, "eosimias.module_path", &module_path) == CONFIG_FALSE) {
            path = ES_LIB_DIR;
        } else {
            path = &module_path;
        }
    }

    assert (path);

    errors = lt_dlsetsearchpath (path);

    fprintf (stderr, "dlsearchpath is %s.\n", path);

    if (errors) {
        free (state);
        return ES_CANT_DLSETSEARCHPATH;
    }

    state->master_lua_state = luaL_newstate();
    luaL_openlibs (state->master_lua_state);

    config_lookup_string(state->cfg, "eosimias.data_store_module", &data_store_module);
    if (!data_store_module) {
        fprintf(stderr, "configuration item 'data_store_module' could not be found.\n");
        free (state);
        return ES_BAD_CONFIG;
    }
    
    errors = find_eosimias_symbol (data_store_module, "open_table", &(state->open_table));
    if (!errors) errors = find_eosimias_symbol (data_store_module, "get", &(state->get));
    if (!errors) errors = find_eosimias_symbol (data_store_module, "put", &(state->put));
    if (!errors) errors = find_eosimias_symbol (data_store_module, "del", &(state->del));
    if (!errors) errors = find_eosimias_symbol (data_store_module, "close_table", &(state->close_table));

    if (errors) {
        free (state);
        return errors;
    }

    eosimias_module_init eosimias_module_init_ref;
    fprintf (stderr, "Getting ready to find the init function for module %s\n", data_store_module);
    errors = find_eosimias_symbol (module, "init", &eosimias_module_init_ref);
    if (!errors) errors = (*eosimias_module_init_ref) (state->cfg, state);

    if (errors) {
        free (state);
        return errors;
    }

    config_lookup_string(state->cfg, "eosimias.event_module", &event_module);
    if (!event_module) {
        fprintf(stderr, "configuration item 'event_module' could not be found.\n");
        free (state);
        return ES_BAD_CONFIG;
    }
    
    errors = find_eosimias_symbol (event_module, "es_new_timer", &(state->new_timer));
    if (!errors) errors = find_eosimias_symbol (event_module, "es_update_timeout", &(state->update_timeout));
    if (!errors) errors = find_eosimias_symbol (event_module, "es_update_associated_data", &(state->update_associated_data));
    if (!errors) errors = find_eosimias_symbol (event_module, "es_delete_timer", &(state->delete_timer));
    if (!errors) errors = find_eosimias_symbol (event_module, "es_watch_fd_for_reads", &(state->watch_fd_for_reads));
    if (!errors) errors = find_eosimias_symbol (event_module, "es_watch_fd_for_writes", &(state->watch_fd_for_writes));
    if (!errors) errors = find_eosimias_symbol (event_module, "es_watch_fd_for_reads_and_writes", &(state->watch_fd_for_reads_and_writes));
    if (!errors) errors =  find_eosimias_symbol (event_module, "es_run", &(state->run));
    if (errors) {
        free (state);
        return errors;
    }

    fprintf (stderr, "Getting ready to find the init function for module %s\n", event_module);
    errors = find_eosimias_symbol (module, "init", &eosimias_module_init_ref);
    if (!errors) errors = (*eosimias_module_init_ref) (state->cfg, state);

    if (errors) {
        free (state);
        return errors;
    }

    return ES_OK;
}

int set_eosimias_module_search_path (char* path) {
    int errors = 0;

    if (path == NULL)
        return ES_BADPARAM;

    errors = lt_dlsetsearchpath (path);

    if (errors)
        return ES_CANT_DLSETSEARCHPATH;

    return ES_OK;
}

int load_eosimias_module (const char *module_name) {
    int errors = 0;
    lt_dlhandle module = NULL;

    if (module_name == NULL)
        return ES_BADPARAM;

    module = lt_dlopenext(module_name);

    if (module == NULL)
        return ES_CANT_DLOPENEXT;

    return ES_OK;
}

int find_eosimias_symbol (const char *module_name, const char *symbol_name, void **reference) {
    lt_dlhandle module = NULL;
    char *errormsg = NULL;

    if (module_name == NULL)
        return ES_BADPARAM;

    if (symbol_name == NULL)
        return ES_BADPARAM;

    module = lt_dlopenext(module_name);

    if (module == NULL)
        return ES_CANT_DLOPENEXT;

    *reference = lt_dlsym (module, symbol_name);

    errormsg = dlerrordup (errormsg);
    if (errormsg != NULL) {
        lt_dlclose (module);
        return ES_CANT_DLSYM;
    }

    lt_dlclose(module);
    return ES_OK;
}

/* **TODO** */
int unload_eocene_module () {
    int errors = 0;

    return ES_OK;
}

static char *dlerrordup (char *errormsg) {
    char *error = (char *) lt_dlerror ();
    if (error && !errormsg)
        errormsg = strdup (error);
    return errormsg;
}

int eosimias_free (struct es_state *state) {

    free (state);

    return ES_OK;
}
