#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ltdl.h>
/*#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>*/
#include "eocene.h"

int libltdl_initialized = 0;

int _eocene_init () {
    int errors = 0;
    errors = lt_dlinit ();
    if (errors)
        return EC_CANT_DLINIT;

    const char *path = getenv (EOCENE_PLUGIN_PATH);
    if (path == NULL) {
        path = LIB_DIR;
    }
    if (path != NULL) {
        errors = lt_dlsetsearchpath (path);
    }

    if (errors)
        return EC_CANT_DLSETSEARCHPATH;

    libltdl_initialized = 1;
    return EC_OK;
}

int set_eocene_module_search_path (char* path) {
    int errors = 0;
    if (!libltdl_initialized) {
        errors = _eocene_init();
        if (errors)
            return errors;
    }

    if (path != NULL) {
        errors = lt_dlsetsearchpath (path);
    }
    if (errors)
        return EC_CANT_DLSETSEARCHPATH;

    return EC_OK;
}

int load_eocene_module (const char *module_name) {
    int errors = 0;
    lt_dlhandle module = NULL;

    if (!libltdl_initialized) {
        errors = _eocene_init();
        if (errors)
            return errors;
    }

    module = lt_dlopenext(module_name);

    if (module == NULL)
        return EC_CANT_DLOPENEXT;

    return EC_OK;
}

int find_eocene_symbol (const char *module_name, const char *symbol_name, void **reference) {
    lt_dlhandle module = NULL;
    char *errormsg = NULL;

    module = lt_dlopenext(module_name);

    if (module == NULL)
        return EC_CANT_DLOPENEXT;

    *reference = lt_dlsym (module, symbol_name);

    errormsg = dlerrordup (errormsg);
    if (errormsg != NULL) {
        lt_dlclose (module);
        return EC_CANT_DLSYM;
    }

    lt_dlclose(module);
    return EC_OK;
}

int unload_eocene_module () {
    int errors = 0;
    if (!libltdl_initialized) {
        errors = _eocene_init();
        if (errors)
            return errors;
    }
    return EC_OK;
}

static char *dlerrordup (char *errormsg) {
  char *error = (char *) lt_dlerror ();
  if (error && !errormsg)
    errormsg = strdup (error);
  return errormsg;
}
