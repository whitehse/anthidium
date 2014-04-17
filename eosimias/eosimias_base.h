
/*
 * Copyright (C) 2014 Dan White
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef EOSIMIAS_BASE_H
#define EOSIMIAS_BASE_H

/* Return types */
#define ES_OK                    0 /* successful result */
#define ES_FAIL                 -1 /* generic failure */
#define ES_NOMEM                -2 /* memory shortage failure */
#define ES_BUFOVER              -3 /* overflowed buffer */
#define ES_BADPARAM             -4 /* invalid parameter supplied */
#define ES_CANT_DLINIT          -5
#define ES_CANT_DLSETSEARCHPATH -6
#define ES_CANT_DLOPENEXT       -7
#define ES_CANT_DLSYM           -8
#define ES_CANT_DLCLOSE         -9
#define ES_CANT_DLEXIT          -10
#define ES_BAD_CONFIG           -11

#ifndef MODULE_PATH_ENV
#  define EOSIMIAS_PLUGIN_PATH    "EOSIMIAS_PLUGIN_PATH"
#endif

#define ES_LIB_DIR         PACKAGE_PKG_LIB_DIR

#define MAX_NUM_OF_SUBMODULES  1024

/* Interface used between main app and storage modules */
typedef int (*es_open_table_cb)(void **db, char *table);
typedef int (*es_put_cb)(void **db, void *key, int key_len, void **value, int *value_len);
typedef int (*es_get_cb)(void **db, void *key, int key_len, void **value, int *value_len);
typedef int (*es_del_cb)(void **db, void *key, int key_len);
typedef int (*es_close_table_cb)(void **db);
typedef int (*es_printer_cb)(void *value, int vartype);

#define ES_READ  1
#define ES_WRITE 2

struct es_timer {
    void *data;
    double when;
    struct es_timer *next;
    struct es_timer *prev;
    void *callback; /* (*es_timer_cb), but it hasn't been defined yet */
};

struct es_timer_list {
    double timeout;
    struct es_timer *head;
    struct es_timer *tail;
    struct es_timer_list *next;
    struct es_timer_list *prev;
};

/* Callback interfaces for the watchers */
typedef int (*es_io_cb)(void *associated_data, int mask);
typedef int (*es_timer_cb)(void *associated_data, struct es_timer *timer);

struct es_io_data {
    void *data;
    es_io_cb callback;
};

/* Interface used betwen main app and event modules */
typedef int (*es_watch_fd_for_reads_cb)(int fd, void *associated_data, es_io_cb io_cb);
typedef int (*es_watch_fd_for_writes_cb)(int fd, void *associated_data, es_io_cb io_cb);
typedef int (*es_watch_fd_for_reads_and_writes_cb)(int fd, void *associated_data, es_io_cb io_cb);
typedef int (*es_run_cb)();

typedef int (*es_new_timer_cb)(void **timer_ref, void **associated_data, double timeout, es_timer_cb timer_cb);
typedef int (*es_update_timeout_cb)(void **timer_ref, double timeout, es_timer_cb timer_cb);
typedef int (*es_update_associated_data_cb)(void **timer_ref, void *associated_data, es_timer_cb timer_cb);
typedef int (*es_delete_timer_cb)(void **timer_ref);

int set_eosimias_module_search_path (char* path);
int load_eosimias_module (const char *module_name);
int find_eosimias_symbol (const char *module_name, const char *symbol_name, void **reference);
int unload_eosimias_module ();
static char *dlerrordup (char *errormsg);

struct es_state {
    es_open_table_cb open_table;
    es_put_cb put;
    es_get_cb get;
    es_del_cb del;
    es_close_table_cb close_table;
    es_new_timer_cb new_timer;
    es_update_timeout_cb update_timeout;
    es_update_associated_data_cb update_associated_data;
    es_delete_timer_cb delete_timer;
    es_watch_fd_for_reads_cb watch_fd_for_reads;
    es_watch_fd_for_writes_cb watch_fd_for_writes;
    es_watch_fd_for_reads_and_writes_cb watch_fd_for_reads_and_writes;
    es_run_cb run;
    /*es_printer_cb printer;*/
    struct config_t *cfg;
    void* master_lua_state;
};

int eosimias_init (struct es_state *state, struct config_t *cfg);

typedef int (*eosimias_module_init)(config_setting_t *config, struct ec_state *_state);

#endif // EOSIMIAS_BASE_H
