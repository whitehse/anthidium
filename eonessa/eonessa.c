#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ltdl.h>
#include "eonessa.h"

int libltdl_initialized = 0;

int _eonessa_init () {
    int errors = 0;
    errors = lt_dlinit ();
    if (errors)
        return EN_CANT_DLINIT;

    const char *path = getenv (EONESSA_PLUGIN_PATH);
    if (path == NULL) {
        path = LIB_DIR;
    }
    if (path != NULL) {
        errors = lt_dlsetsearchpath (path);
    }

    if (errors)
        return EN_CANT_DLSETSEARCHPATH;

    libltdl_initialized = 1;
    return EN_OK;
}

int set_eonessa_module_search_path (char* path) {
    int errors = 0;
    if (!libltdl_initialized) {
        errors = _eonessa_init();
        if (errors)
            return errors;
    }

    if (path != NULL) {
        errors = lt_dlsetsearchpath (path);
    }
    if (errors)
        return EN_CANT_DLSETSEARCHPATH;

    return EN_OK;
}

int load_eonessa_module (const char *module_name) {
    int errors = 0;
    lt_dlhandle module = NULL;

    if (!libltdl_initialized) {
        errors = _eonessa_init();
        if (errors)
            return errors;
    }

    module = lt_dlopenext(module_name);

    if (module == NULL)
        return EN_CANT_DLOPENEXT;

    return EN_OK;
}

int find_eonessa_symbol (const char *module_name, const char *symbol_name, void **reference) {
    lt_dlhandle module = NULL;
    char *errormsg = NULL;

    module = lt_dlopenext(module_name);

    if (module == NULL)
        return EN_CANT_DLOPENEXT;

    *reference = lt_dlsym (module, symbol_name);

    errormsg = dlerrordup (errormsg);
    if (errormsg != NULL) {
        lt_dlclose (module);
        return EN_CANT_DLSYM;
    }

    lt_dlclose(module);
    return EN_OK;
}

int unload_eonessa_module () {
    int errors = 0;
    if (!libltdl_initialized) {
        errors = _eonessa_init();
        if (errors)
            return errors;
    }
    return EN_OK;
}

static char *dlerrordup (char *errormsg) {
  char *error = (char *) lt_dlerror ();
  if (error && !errormsg)
    errormsg = strdup (error);
  return errormsg;
}

void print_line(const char *line, unsigned n) {
    int i;
    int display_width=16;

    for(i=0;i<n;i++)
        fprintf(stderr, "%02x ", (unsigned char)line[i]);
    for(i=n;i<display_width;i++)
        fprintf(stderr, "   ");
    fprintf(stderr, " ");
    for(i=0;i<n;i++)
        if(isgraph((unsigned) line[i]))
            fprintf(stderr, "%c", line[i]);
        else
            fprintf(stderr, ".");
        fprintf(stderr, "\n");
}

void dump_buffer(const char* dump, unsigned n) {
    int i;

    if (dump == NULL) { return; }

    for (i=0;i<n;i+=16) {
        if(i + 16 <= n)
            print_line(dump+i, 16);
        else
            print_line(dump+i, n - i);
    }
}

