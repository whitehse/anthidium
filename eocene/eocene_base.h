
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

#ifndef EOCENE_BASE_H
#define EOCENE_BASE_H

/* Return types */
#define EC_OK                    0 /* successful result */
#define EC_FAIL                 -1 /* generic failure */
#define EC_NOMEM                -2 /* memory shortage failure */
#define EC_BUFOVER              -3 /* overflowed buffer */
#define EC_BADPARAM             -4 /* invalid parameter supplied */
#define EC_CANT_DLINIT          -5
#define EC_CANT_DLSETSEARCHPATH -6
#define EC_CANT_DLOPENEXT       -7
#define EC_CANT_DLSYM           -8
#define EC_CANT_DLCLOSE         -9
#define EC_CANT_DLEXIT          -10

#define EC_CAP_TYPE_PCAP 1

#ifndef MODULE_PATH_ENV
#  define EOCENE_PLUGIN_PATH    "EOCENE_PLUGIN_PATH"
#endif

#define LIB_DIR         PACKAGE_PKG_LIB_DIR

#define MAX_NUM_OF_SUBMODULES   128

/* Interface used between modules and the main app */
//typedef int (*ec_use_table_cb)(void **db, char *table);
//typedef int (*ec_store_cb)(void **db, void *key, int key_len, void **value, int *value_len);
//typedef int (*ec_retrieve_cb)(void **db, void *key, int key_len, void **value, int *value_len);
//typedef int (*ec_rem_cb)(void **db, void *key, int key_len);
//typedef int (*ec_unuse_table_cb)(void **db);

/* Interface used between main app and storage modules */
typedef int (*ec_open_table_cb)(void **db, char *table);
typedef int (*ec_put_cb)(void **db, void *key, int key_len, void **value, int *value_len);
typedef int (*ec_get_cb)(void **db, void *key, int key_len, void **value, int *value_len);
typedef int (*ec_del_cb)(void **db, void *key, int key_len);
typedef int (*ec_close_table_cb)(void **db);
typedef int (*ec_printer_cb)(void *value, int vartype);

#define EC_READ  1
#define EC_WRITE 2

struct ec_timer {
    void *data;
    double when;
    struct ec_timer *next;
    struct ec_timer *prev;
    void *callback; /* (*ec_timer_cb), but it hasn't been defined yet */
};

struct ec_timer_list {
    double timeout;
    struct ec_timer *head;
    struct ec_timer *tail;
    struct ec_timer_list *next;
    struct ec_timer_list *prev;
};

/* Callback interfaces for the watchers */
typedef int (*ec_io_cb)(void *associated_data, int mask);
typedef int (*ec_timer_cb)(void *associated_data, struct ec_timer *timer);

struct ec_io_data {
    void *data;
    ec_io_cb callback;
};

/*struct ec_timer_data {
    void *data;
    ec_timer_cb callback;
};*/

/* Interface used betwen main app and event modules */
typedef int (*ec_watch_fd_for_reads_cb)(int fd, void *associated_data, ec_io_cb io_cb);
typedef int (*ec_watch_fd_for_writes_cb)(int fd, void *associated_data, ec_io_cb io_cb);
typedef int (*ec_watch_fd_for_reads_and_writes_cb)(int fd, void *associated_data, ec_io_cb io_cb);
typedef int (*ec_run_cb)();

typedef int (*ec_new_timer_cb)(void **timer_ref, void **associated_data, double timeout, ec_timer_cb timer_cb);
typedef int (*ec_update_timeout_cb)(void **timer_ref, double timeout, ec_timer_cb timer_cb);
typedef int (*ec_update_associated_data_cb)(void **timer_ref, void *associated_data, ec_timer_cb timer_cb);
typedef int (*ec_delete_timer_cb)(void **timer_ref);

int set_eocene_module_search_path (char* path);
int load_eocene_module (const char *module_name);
int find_eocene_symbol (const char *module_name, const char *symbol_name, void **reference);
int unload_eocene_module ();
static char *dlerrordup (char *errormsg);

struct ec_state {
    ec_open_table_cb open_table;
    ec_put_cb put;
    ec_get_cb get;
    ec_del_cb del;
    ec_close_table_cb close_table;
    ec_new_timer_cb new_timer;
    ec_update_timeout_cb update_timeout;
    ec_update_associated_data_cb update_associated_data;
    ec_delete_timer_cb delete_timer;
    ec_watch_fd_for_reads_cb watch_fd_for_reads;
    ec_watch_fd_for_writes_cb watch_fd_for_writes;
    ec_watch_fd_for_reads_and_writes_cb watch_fd_for_reads_and_writes;
    ec_run_cb run;
    ec_printer_cb printer;
    struct config_t *cfg;
    void* master_lua_state;
};

typedef int (*eocene_init)(config_setting_t *config, struct ec_state *_state);
typedef int (*eocene_wireline_parse)(const char* buf, unsigned n, int capture_type);
void dump_buffer(const char* buf, unsigned n);

#endif // EOCENE_BASE_H
