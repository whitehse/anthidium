
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

#define EC_CAP_TYPE_PCAP 1

/*
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
*/

typedef int (*eocene_wireline_parse)(const char* buf, unsigned n, int capture_type);

#endif // EOCENE_BASE_H
